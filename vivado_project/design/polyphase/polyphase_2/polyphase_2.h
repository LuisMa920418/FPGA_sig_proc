// =====================================================================================
// 
//       Filename:  polyphase_2.h
// 
//    Description:  
// 
//        Version:  1.0
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Mathieu Lebon (ML), 
//        Company:  Thales Alenia Space
// 
// =====================================================================================

#ifndef __POLY_2__
#define __POLY_2__

#include "hls.h"
#include "c_polyphase.hpp"

namespace sp_poly_2 {

	typedef c_complex<ap_int<11> > t_in;
	typedef c_complex<ap_int<22> > t_acc;
	typedef c_complex<ap_int<12> > t_out;
	typedef ap_int<11>             t_coef;

  static const int filter_size = 12;
  static const int shift       = 10;

  typedef c_polyphase<filter_size,t_in,t_coef,t_acc,shift,t_out> t_polyphase;

};

void poly_2(hls::stream<sp_poly_2::t_in> & in, hls::stream<sp_poly_2::t_out> & out);

#endif

