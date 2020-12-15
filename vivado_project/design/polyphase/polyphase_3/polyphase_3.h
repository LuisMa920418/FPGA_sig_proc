// =====================================================================================
// 
//       Filename:  polyphase_3.h
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

#ifndef __POLY_3__
#define __POLY_3__

#include "hls.h"
#include "c_polyphase.hpp"

namespace sp_poly_3 {

	typedef c_complex<ap_int<12> > t_in;
	typedef c_complex<ap_int<24> > t_acc;
	typedef c_complex<ap_int<14> > t_out;
	typedef ap_int<12>             t_coef;

  static const int filter_size = 32;
  static const int shift       = 10;

  typedef c_polyphase<filter_size,t_in,t_coef,t_acc,shift,t_out> t_polyphase;

}

void poly_3(hls::stream<sp_poly_3::t_in> & in, hls::stream<sp_poly_3::t_out> & out);

#endif

