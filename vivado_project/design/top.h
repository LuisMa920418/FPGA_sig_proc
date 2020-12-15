// =====================================================================================
// 
//       Filename:  top.h
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

#ifndef __TOP__
#define __TOP__

#include "polyphase/top_poly.h"
#include "fft/fft.h"

namespace sp_design {

  typedef sp_poly::t_in      t_in;
  typedef sp_fft::t_data_mem t_out;

  void top(ac_channel<t_in> & in, t_out * mem_out);

};

#endif

