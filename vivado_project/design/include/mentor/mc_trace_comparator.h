////////////////////////////////////////////////////////////////////////////////
// Catapult Synthesis
// 
// Copyright (c) 2003-2011 Calypto Design Systems, Inc.
//       All Rights Reserved
// 
// This document contains information that is proprietary to Calypto Design
// Systems, Inc. The original recipient of this document may duplicate this  
// document in whole or in part for internal business purposes only, provided  
// that this entire notice appears in all copies. In duplicating any part of  
// this document, the recipient agrees to make every reasonable effort to  
// prevent the unauthorized use and distribution of the proprietary information.
//
////////////////////////////////////////////////////////////////////////////////

// This file is part of catapult, not part of the design.

/*! \file ac_trace_comparator.h
  \brief Catapult builtins
  This class replaces mc_comparator.h in the testbench  when it is generated for tracing RTL channel data (see generated mc_testbench.h) .
*/

#ifndef MC_TRACE_COMPARATOR_H
#define MC_TRACE_COMPARATOR_H

#include <sstream>
#include <iomanip>
#include <systemc.h>
#include <tlm.h>

#include <mc_container_types.h>
#include <mc_comparator.h>
#include <mc_type_to_string.h>
#include <ac_trace_replay.h>

template<class Tclass>
struct mc_trace_report_data {

  void report(const char* id,
				const Tclass& golden_value, const Tclass& dut_value) {
    std::ostringstream msg;
    msg.str(""); msg << "             C++ = " << golden_value;
    SC_REPORT_INFO(id, msg.str().c_str());
    msg.str(""); msg << "             DUT = " << dut_value;
    SC_REPORT_INFO(id, msg.str().c_str());
  }
  
  bool partial_compare(const char* id, const Tclass& golden_value) { return false; }
};

template<class Tclass, int Tsize>
struct mc_trace_report_data< mgc_sysc_ver_array1D<Tclass,Tsize> >
{
  void report(const char* id,
              const mgc_sysc_ver_array1D<Tclass,Tsize>& golden_value,
              const mgc_sysc_ver_array1D<Tclass,Tsize>& dut_value)
  {
    int LB = (golden_value.get_lower() < 0) ? 0       : golden_value.get_lower();
    int UB = (golden_value.get_upper() < 0) ? Tsize-1 : golden_value.get_upper();
    std::ostringstream msg;
    msg << std::setw(3+6) << "index" <<  ' '
        << std::setw(20) << "C++ value" << ' '
        << std::setw(20) << "dut value";
    SC_REPORT_INFO(id, msg.str().c_str());
    for (int i = 0; i < Tsize; ++i) {
      msg.str("");
      if (i<LB || i>UB) msg << " - ";
      else msg << (golden_value[i] == dut_value[i] ? "===" : "###");
      msg << std::setw(6) << i << ' '
          << std::setw(20) << golden_value[i] << ' '
          << std::setw(20) << dut_value[i];
      SC_REPORT_INFO(id, msg.str().c_str());
    }
  }
  bool partial_compare(const char* id, const mgc_sysc_ver_array1D<Tclass,Tsize>& golden_value) {
    int LB = (golden_value.get_lower() < 0) ? 0       : golden_value.get_lower();
    int UB = (golden_value.get_upper() < 0) ? Tsize-1 : golden_value.get_upper();
    if ((LB != 0) || (UB != Tsize-1)) {
       std::ostringstream msg;
       msg.str(""); msg << "Array element range comparison limited from [0..." << Tsize-1 << "] to [" << LB << "..." << UB << "]";
       SC_REPORT_INFO(id, msg.str().c_str());
       return true;
    }
    return false;
  }
};


template<class Tclass>
struct mc_trace_recurse {
	void trace_recursive(Tclass& dut_value, TRData *fileTrace, int itr)
	{	
		// set DUT result to TRACE file
		string sdat;
		type_to_string(dut_value, sdat);
		TraceReplay::inst()->trace_complex_item(fileTrace, sdat);
	}
};

template<class Tclass, int Tsize>
struct mc_trace_recurse< mgc_sysc_ver_array1D<Tclass,Tsize> >;

template<class Tclass, int Tsize>
struct mc_trace_recurse< mgc_sysc_ver_array1D<Tclass,Tsize> >
{
	void trace_recursive(const mgc_sysc_ver_array1D<Tclass,Tsize>& dut_value, TRData *fileTrace, int itr)
	{		
		for (int i = 0; i < Tsize; ++i) {
			// set DUT result to TRACE file
			Tclass item = dut_value[i];
			tr.trace_recursive(item, fileTrace, itr);
		}
	}
	
	mc_trace_recurse<Tclass> tr;
};

template<class Tclass>
struct mc_trace_data {
  void trace(TRData *fileTrace, int itr, Tclass& dut_value, int num_items) {	
		// set DUT result to TRACE file
		string sdat;
		type_to_string(dut_value, sdat);
		TraceReplay::inst()->trace_output(fileTrace, sdat);
	}
};

template<class Tclass, int Tsize>
struct mc_trace_data< mgc_sysc_ver_array1D<Tclass,Tsize> >
{
	void trace(TRData *fileTrace, int itr, const mgc_sysc_ver_array1D<Tclass,Tsize>& dut_value, int num_items)
	{
		TraceReplay::inst()->trace_complex_begin(fileTrace, num_items);		
		for (int i = 0; i < Tsize; ++i) {
			// make recursive call to flatten strcts and arrays
			Tclass item = dut_value[i];
			tr.trace_recursive(item, fileTrace, itr);
		}
		TraceReplay::inst()->trace_complex_end(fileTrace);	

	}
	
	mc_trace_recurse<Tclass> tr;
};

template <class Tclass, class Tmask> 
SC_MODULE(mc_trace_comparator)
{    
  sc_port< tlm::tlm_fifo_get_if<Tclass> >                  data_in;
  sc_port< tlm::tlm_fifo_get_if<mc_golden_info<Tclass,Tmask> > > data_golden;
 
  int  get_compare_count() const { return _compare_cnt*_chan_factor; }
  int  get_partial_compare_count() const { return _partial_compare_cnt*_chan_factor; }
  int  get_mask_compare_count() const { return _mask_compare_cnt*_chan_factor; }
  int  get_ignore_count() const { return _ignore_cnt*_chan_factor; }
  int  get_error_count() const { return _error_cnt*_chan_factor; }
  int  get_success_count() const { return (_compare_cnt - _error_cnt - _ignore_cnt)*_chan_factor; }
  bool get_last_comparison_result() const { return _last_result; }

  /* triggers after each comparison; the above functions will include
     the data of this comparison.
  */
  const sc_event& get_compare_event() const { return _compare; }

  /* triggers after each failing comparison; the above functions will
     include the data of this comparison.
  */
  const sc_event& get_error_event() const { return _error; }

  /* triggers after each successful comparison; the above functions
     will include the data of this comparison.
  */
  const sc_event& get_success_event() const { return _success; }

  /* triggers after each suppressed comparison; the above functions
     will include the data of this comparison.
  */
  const sc_event& get_ignore_event() const { return _ignore; }

  SC_HAS_PROCESS(mc_trace_comparator);
  explicit mc_trace_comparator(const sc_module_name& name, int max_error_cnt = -1, int chan_factor = 1) 
    : sc_module(name)
    , data_in("data_in")
    , data_golden("data_golden")
    , _error_max(max_error_cnt)
    , _chan_factor(chan_factor)
	, num_items(0)
	, fileTrace(NULL)
    {
	
      SC_METHOD(compare);
    }

  virtual void start_of_simulation() {
    _compare_cnt = 0;
    _partial_compare_cnt = 0;
    _mask_compare_cnt = 0;
    _ignore_cnt  = 0;
    _error_cnt   = 0;
    _received_golden = false;
    _received_dut = false;
  }
  
   void setup_trace_file(const char *tname, int ele_count)
   {
		num_items = ele_count;
	    fileTrace = TraceReplay::inst()->get_trace_data(tname, TRData::OUTPUT);
   }

 private:
  void compare();
  
  int                _compare_cnt;
  int                _partial_compare_cnt;
  int                _mask_compare_cnt;
  int                _ignore_cnt;
  int                _error_cnt;
  const int          _error_max;
  const int          _chan_factor;
  bool               _last_result;

  sc_event           _compare;
  sc_event           _ignore;
  sc_event           _success;
  sc_event           _error;

  mc_golden_info<Tclass,Tmask>  _golden;
  Tclass                  _dut;
  bool               _received_golden;
  bool               _received_dut;
  std::ostringstream _msg;
  
  // trace stuff
  mc_trace_report_data<Tclass>  _rpt;
  mc_trace_data<Tclass>   _trace;
  int        num_items;
 
  // to send DUT output to trace file
  TraceData *fileTrace;
};

template <class Tclass, class Tmask>
void mc_trace_comparator<Tclass,Tmask>::compare()
{
  while (true) {
    if (!_received_golden && data_golden->nb_get(_golden))
    {
#ifdef CCS_SYSC_DEBUG
      _msg.str("");
      _msg << "obtained C++ value " 
            << _golden._data << " @ " << sc_time_stamp();
      SC_REPORT_INFO(name(), _msg.str().c_str());
#endif
      _received_golden = true;
    }

    if (!_received_dut && data_in->nb_get(_dut))
    {
#ifdef CCS_SYSC_DEBUG
      _msg.str("");
      _msg << " obtained DUT    value " 
            << _dut << " @ " << sc_time_stamp();
      SC_REPORT_INFO(name(), _msg.str().c_str());
#endif
      _received_dut = true;
    }

    if (!_received_dut || !_received_golden) break;
    
    ++_compare_cnt;
    if (_rpt.partial_compare(name(), _golden._data)) ++_partial_compare_cnt;

    if (_golden._use_mask) {
#ifdef CCS_SYSC_DEBUG
      SC_REPORT_INFO(name(), "Masking golden value and DUT value");
      _msg.str(""); _msg << "Before mask: C++ value = " << _golden._data;
      SC_REPORT_INFO(name(), _msg.str().c_str());
      _msg.str(""); _msg << "                HDL value = " << _dut;
      SC_REPORT_INFO(name(), _msg.str().c_str());
#endif
      _golden._data &= _golden._mask;
      _dut &= _golden._mask;
       ++_mask_compare_cnt;
#ifdef CCS_SYSC_DEBUG
      _msg.str(""); _msg << "After  mask: C++ value = " << _golden._data;
      SC_REPORT_INFO(name(), _msg.str().c_str());
      _msg.str(""); _msg << "                HDL value = " << _dut;
      SC_REPORT_INFO(name(), _msg.str().c_str());
#endif
    }
    _last_result = (_golden._data == _dut);
	
	// don't know how/if this plays.......
    if (_golden._ignore) {
      ++_ignore_cnt;
#ifdef CCS_SYSC_DEBUG
      SC_REPORT_INFO(name(), "Ignoring Data");
#endif
      _ignore.notify(SC_ZERO_TIME);
    }
    else if (_last_result) {
#ifdef CCS_SYSC_DEBUG
      SC_REPORT_INFO(name(), "Correct Data Detected");
#endif
      _success.notify(SC_ZERO_TIME);
    } else {
	 ++_error_cnt;
	 if (_error_max <= 0 || _error_cnt <= _error_max) {
	  // report mis-match as Info
      _msg.str(""); _msg << "Data mis-match @ " << sc_time_stamp();
      SC_REPORT_INFO(name(), _msg.str().c_str());
      _msg.str(""); _msg << " iteration count = " << _golden._iteration;
      SC_REPORT_INFO(name(), _msg.str().c_str());
	  
	  // other report elements removed
		_rpt.report(name(), _golden._data, _dut);
	  }

      // not an error ??  _error.notify(SC_ZERO_TIME);
    }

	if (fileTrace) _trace.trace(fileTrace, _golden._iteration, _dut, num_items);
	
    _compare.notify(SC_ZERO_TIME);

    // Can't stop if we are tracing for replay
	 if (_error_max > 0 && _error_cnt == _error_max) {
	  _msg.str(""); _msg << "Reached Maximum mis-match reports.";
	  SC_REPORT_INFO(name(), _msg.str().c_str());
    }

    _received_dut = _received_golden = false;
  }

  if (_received_dut) {
    next_trigger(data_golden->ok_to_get()); // waiting for golden data
  } else if (_received_golden) {
    next_trigger(data_in->ok_to_get()); // waiting for dut data
  } else {
    next_trigger(data_golden->ok_to_get() | data_in->ok_to_get());
  }
}

#endif //MC_COMPARATOR_H
