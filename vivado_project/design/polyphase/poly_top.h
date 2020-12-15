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

#ifndef __TOP_POLY__
#define __TOP_POLY__

#include "polyphase_1/polyphase_1.h"
#include "polyphase_2/polyphase_2.h"
#include "polyphase_3/polyphase_3.h"

namespace sp_poly_top {

	typedef sp_poly_1::t_in  t_in;
	typedef sp_poly_3::t_out t_out;

};

void poly_top(hls::stream<sp_poly_top::t_in> & in, hls::stream<sp_poly_top::t_out> & out);

#endif

