#ifndef MC_REPLAY_COMPARATOR_H
#define MC_REPLAY_COMPARATOR_H

#include <sstream>
#include <string>
#include <iomanip>

#include "ac_trace_replay.h"

template<class Tclass>
struct tr_report_data {
	void report(string &name, const Tclass& data, const Tclass& dut) {
		cout << name << ":            C++ = " << data << "  DUT = " << dut << endl;
		// todo - we may want to try to see if we can resync if iteration is also different we may have dropped data
	}
};

template<class Tclass, int Tsize>
struct tr_report_data< mgc_sysc_ver_array1D<Tclass,Tsize> >
{
	void report(
		string &name,
		const mgc_sysc_ver_array1D<Tclass,Tsize>& data,
		const mgc_sysc_ver_array1D<Tclass,Tsize>& dut
	)
	{
		cout << std::setw(3+6) << "index" <<  ' '
			<< std::setw(20) << "C++ value" << ' '
			<< std::setw(20) << "dut value" << endl;
		for (int i = 0; i < Tsize; ++i) {
			cout << ((data[i] == dut[i]) ? "===" : "ERR");
			cout << std::setw(6) << i << ' '
			  << std::setw(20) << data[i] << ' '
			  << std::setw(20) << dut[i] << endl;
		}
	}
};

template <class Tclass, class Tmask> 
class mc_replay_comparator
{    
public:
  int  get_compare_count() const { return _compare_cnt*_chan_factor; }
  int  get_partial_compare_count() const { return _partial_compare_cnt*_chan_factor; }
  int  get_mask_compare_count() const { return _mask_compare_cnt*_chan_factor; }
  int  get_ignore_count() const { return _ignore_cnt*_chan_factor; }
  int  get_error_count() const { return _error_cnt*_chan_factor; }
  int  get_success_count() const { return (_compare_cnt - _error_cnt - _ignore_cnt)*_chan_factor; }

  mc_replay_comparator(const char *name, int max_error_cnt = -1, int chan_factor = 1, bool verbose = 0) 
    : _name(name)
	, _error_max(max_error_cnt)
	, _chan_factor(chan_factor)
	, _compare_cnt(0)
    , _partial_compare_cnt(0)
    , _mask_compare_cnt(0)
    , _ignore_cnt(0)
    , _error_cnt(0)
	, _verbose(verbose)
	, _use_mask(false)
	, _hdl_result(NULL)
    {
		setup_trace_file(name);
	}
  
   bool setup_trace_file(const char *name)
   {
		_hdl_result = ac_channel_pipe_replay< Tclass >::get_output_replay_port(name);
		
		if (_hdl_result == NULL) {
			cout << name << ": Error unable to locate traced data for this output. It will be ignored." << endl;
		}
		return (_hdl_result != NULL);
   }
   
   bool trace_found()
   {
		return (_hdl_result != NULL);
   }
   
   // called by client when C++ result is available
   bool compare(
	Tclass &data
	// , Tmask mask
	, int citr
	);
	
	// output messages regarding results
	bool report_output_summary();

private:
 
  string             _name;
  const int          _error_max;
  const int          _chan_factor;
  int                _compare_cnt;
  int                _partial_compare_cnt;
  int                _mask_compare_cnt;
  int                _ignore_cnt;
  int                _error_cnt;
 
  bool _verbose;
  bool _use_mask;
 
  ac_channel_replay< Tclass >  *_hdl_result;
  
  tr_report_data<Tclass>  _rpt;
};

template <class Tclass, class Tmask>
bool mc_replay_comparator<Tclass,Tmask>::compare(
	Tclass &data
	//, Tmask mask
	, int citr
)
{	
	Tclass dut;
	int size = _hdl_result->get_output(dut);
	
	// if there was no traced output data then the test is complete as far as we're concerned
	if (size < 0) {
		return false;
	}
	
	++_compare_cnt;

	// need to apply mask
 //   if (_use_mask) {
//      data &= mask;
//      dut &= mask;
 //     ++_mask_compare_cnt;
//   }
//    if (_golden._ignore) {
//      ++_ignore_cnt;
	
	// todo golden.ignore ?? don't know how/if this plays.......
    if (data == dut) {
		if ( _verbose ) {
		    // todo type????
			// cout << _name << ": (Test iteration " << citr <<  ") data match: " << data << endl;
		}
    } else {
		++_error_cnt;
		if (_error_max <= 0 || _error_cnt <= _error_max) {
			// report mis-match as Info
			cout << _name << ": Data mis-match @ iteration " << citr << endl;
			_rpt.report(_name, data, dut);
		}
    }
	
    // output message at end ot max warnings
	 if (_error_max > 0 && _error_cnt == _error_max) {
	  cout << "Warning: " <<  _name << ": Reached Maximum error report count." << endl;
    }
	return true;
}

template <class Tclass, class Tmask>
bool mc_replay_comparator<Tclass,Tmask>::report_output_summary()
{
	return (_hdl_result) ? _hdl_result->report_output_summary() : false;
}

#endif
