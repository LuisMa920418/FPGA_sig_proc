// =====================================================================================
// 
//        @file   filter_std.cpp
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

#include "filter_sym.h"

using namespace sp_filter_sym;

void filter_sym(hls::stream<t_in> & in, hls::stream<t_acc> & out) {

#pragma HLS interface ap_ctrl_none port=return
#pragma HLS INLINE
	// For synthesis : Add pipeline pragma (II=1)


// same steps as in the case standard filter

t_filter instantiated_filter;  //instantiation of the filter

	static const t_coef coef[] = {10,22,31};


	t_in  d_in;
	t_acc d_out;

	  //get the input to the filter
	d_in = in.read();
	//executes the main process of the filter
	instantiated_filter.process(d_in,&coef, d_out);
	//outputs the result of the filtering
    out.write(d_out);

}

