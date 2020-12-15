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

#ifndef __STIM_H__
#define __STIM_H__

#include <ac_int.h>
#include <ac_complex.h>
#include <ac_channel.h>
#include "reference.h"

namespace sp_stim {

  typedef ac_complex<int10> t_out;

  void top(ac_channel<t_out> & out);

};

#endif

