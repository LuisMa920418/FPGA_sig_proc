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

#ifndef __ram_sync_single_be_h
#define __ram_sync_single_be_h

#include <systemc.h>

#pragma map_to_operator RAM_single
template <int ram_id, int words, int width, int addr_width, int a_reset_active, int s_reset_active, int enable_active, int re_active, int we_active, int num_byte_enables, int clock_edge, int no_of_RAM_readwrite_port>
SC_MODULE(ram_sync_single_be) {

  //  Ports
  sc_in<sc_lv<width> > data_in;
  sc_in<sc_lv<addr_width> > addr;
  sc_in<sc_lv<num_byte_enables> > re;
  sc_in<sc_lv<num_byte_enables> > we;
  sc_out<sc_lv<width> > data_out;
  sc_in<bool> clk;
  sc_in<sc_logic> a_rst;
  sc_in<sc_logic> s_rst;
  sc_in<sc_logic> en;

  sc_lv<width>                  mem[words];

  sc_logic phase_en;

  const int byte_width;

  //  Constructor 'rtl'
  SC_CTOR(ram_sync_single_be) :
    data_in("data_in"),
    addr("addr"),
    re("re"),
    we("we"),
    data_out("data_out"),
    clk("clk"),
    a_rst("a_rst"),
    s_rst("s_rst"),
    en("en"),
    byte_width(width / num_byte_enables)
  {
#ifndef __SYNTHESIS__
    for ( int i = 0; i < words; ++i )
      mem[i] = 0;
    phase_en = (enable_active ? SC_LOGIC_1 : SC_LOGIC_0);
    SC_METHOD(seq_proc);
    sensitive << (clock_edge ? clk.pos() : clk.neg());
    dont_initialize();
#endif
  }

#ifndef __SYNTHESIS__
  bool is_valid_addr() {
    return addr.read().is_01() && addr.read().to_uint() < words;
  }


  void seq_proc() {
    if ( en.read() == phase_en ) {
      const unsigned addr_val = addr.read().to_uint();
      for (int i = 0; i < num_byte_enables; i++) {
        if (re.read()[i] == sc_logic(re_active) ) {
          if ( addr.read().is_01() ) {
            if (addr_val >= words)
              SC_REPORT_FATAL(name(), "addr_in is out of bounds");
            data_out = mem[addr_val].range((i + 1)*byte_width-1, i*byte_width);   
          }
          else {
            SC_REPORT_WARNING(name(), "addr_in contains 'X' or 'Z' -- converting to 0");
            data_out = mem[0];
          }
        }
        if ( we.read()[i] == sc_logic(we_active) ) {
          if ( addr.read().is_01() ) {
            if (addr_val >= words)
              SC_REPORT_FATAL(name(), "addr_in is out of bounds");
            sc_lv<width> mem_word = mem[addr_val];
            mem_word.range((i+1)*byte_width-1, i*byte_width) = data_in.read().range((i+1)*byte_width-1, i*byte_width);
            mem[addr_val] = mem_word;
          } else {
            SC_REPORT_WARNING(name(), "addr_in contains 'X' or 'Z' for write operation");
            mem[0] = data_in;
          }
        }
      }
    }
  }
#endif
};
#endif // __ram_sync_single_be_h

