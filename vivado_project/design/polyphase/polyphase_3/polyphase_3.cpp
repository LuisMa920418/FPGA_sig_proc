// =====================================================================================
// 
//        @file   polyphase_3.cpp
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

#include "polyphase_3.h"

using namespace sp_poly_3;

void poly_3(hls::stream<t_in> & in, hls::stream<t_out> & out) {

#pragma HLS interface ap_ctrl_none port=return
#pragma HLS INLINE
	// For synthesis : Add pipeline pragma (II=1)

	static const t_coef coef_1[] = {-4, 10, -19, 35, -61, 106, -202, 647};
	static const t_coef coef_2[] = {0,  0,  0,   0,  0,   0,   0,    0, 1024, 0, 0, 0, 0, 0, 0, 0};

	t_polyphase instantiated_filter;  //instantiation of the filter

	//executes the main process of the filter
	instantiated_filter.process(in,coef_1,coef_2, out);
}

