// =====================================================================================
// 
//       Filename:  fft.h
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

#ifndef __FFT_H__
#define __FFT_H__

#include "hls.h"
#include "c_fft.hpp"

namespace sp_fft {

  typedef c_complex<ap_int<14> > t_in;
  typedef c_complex<ap_int<19> > t_data_mem;
  typedef c_complex<ap_int<13> > t_coef;

  static const int fft_size             = 64;
  static const int butterfly_lsb_delete = 11;

  typedef c_fft<fft_size,t_data_mem,t_coef,butterfly_lsb_delete> t_fft;

};

void fft(hls::stream<sp_fft::t_in> & in, sp_fft::t_data_mem mem_out[64]);

#endif
