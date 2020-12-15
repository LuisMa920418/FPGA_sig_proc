// =====================================================================================
// 
//       Filename:  filter_sym.h
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

#ifndef __FILTER_SYM__
#define __FILTER_SYM__

#include "hls.h"
#include "c_filter.hpp"

namespace sp_filter_sym {

  typedef c_complex<ap_int<10> > t_in;
  typedef c_complex<ap_int<21> > t_acc;
  typedef ap_int<11>             t_coef;

  static const int filter_size = 6;

  typedef c_filter<symmetric,t_in,t_coef,t_acc,filter_size> t_filter;

};

void filter_sym(hls::stream<sp_filter_sym::t_in> & in, hls::stream<sp_filter_sym::t_acc> & out);

#endif

