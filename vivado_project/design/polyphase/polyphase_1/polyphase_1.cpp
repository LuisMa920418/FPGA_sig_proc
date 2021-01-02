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

	static const t_coef coef_1[] = {13, -65, 309};  //implemented as symmetric filter order 6, using these coefficients
	static const t_coef coef_2[] = {0,  0,   0, 512, 0, 0}; //implemented as symmetric filter order 7(using these coefficients) or just a shifter by log2(512)=9, 
	
	// #toask how does HLS sinthetizes  this: out = in*512, using a multiplier or using shifter?
    // sum(abs(filter_coefficients))=1286;
	
   //#toask :  have  these coefficients the same format than those passed as arguments to the filter when 
   // there is just one branch? These coefficients are in a format specific to be used for two branches ... 

	/*
	filter coefficients:
	amp=[1 1 0 0];
    f=[0 0.25 0.75 1];
	coef = firpm(10, f,amp);
	  or 
	coef = remez(10,f,amp);
	then convert to signed integer 10 bits
	coef = round(2^10*coef);

	
	*/
	

	t_polyphase instantiated_filter;  //instantiation of the filter

	//executes the main process of the filter
	instantiated_filter.process(in,&coef_1,&coef_2, out);
}

