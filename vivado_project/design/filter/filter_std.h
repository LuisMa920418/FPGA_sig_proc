// =====================================================================================
// 
//       Filename:  filter_std.h
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

#ifndef __FILTER_STD__
#define __FILTER_STD__

#include "hls.h"
#include "c_filter.hpp"

namespace sp_filter_std {

  typedef c_complex<ap_int<10> > t_in;
  typedef c_complex<ap_int<21> > t_acc;
  typedef ap_int<11>                t_coef;

  static const int filter_size = 6; 

  typedef c_filter<standard,t_in,t_coef,t_acc,filter_size> t_filter;

};
//sdqsndjkqsnjkn
void filter_std(hls::stream<sp_filter_std::t_in> & in, hls::stream<sp_filter_std::t_acc> & out);

#endif

