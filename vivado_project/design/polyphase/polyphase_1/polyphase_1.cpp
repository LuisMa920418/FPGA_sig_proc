// =====================================================================================
// 
//        @file   polyphase_1.cpp
// 
//       @brief   
//
//    @internal
//      Version:  1.0
//     Revision:  none
//     Compiler:  g++
// 
//     @author    Mathieu Lebon (ML), 
//     Company:   Thales Alenia Space
// 
// =====================================================================================

#include "polyphase_1.h"

using namespace sp_poly_1;

void poly_1(hls::stream<t_in> & in, hls::stream<t_out> & out) {

#pragma HLS interface ap_ctrl_none port=return
#pragma HLS INLINE
	// Synthesis : Add pipeline pragma (II=1)

	static const t_coef coef_1[] = {13, -65, 309};
	static const t_coef coef_2[] = {0,  0,   0, 512, 0, 0};

	// ...
}

