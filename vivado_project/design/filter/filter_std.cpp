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

#include "filter_std.h"
#include "c_filter.hpp"

using namespace sp_filter_std;

void filter_std(hls::stream<t_in> & in, hls::stream<t_acc> & out) {

#pragma HLS interface ap_ctrl_none port=return
#pragma HLS INLINE
	// For synthesis : Add pipeline pragma
	// Try to generate several architectures :
	// - FIR mac engine
	// - FIR mac farm
	// - FIR full parallel
	// Doc (internet) : Vivado HLS User Guide (UG902)

	static const t_coef coef[] = {10,22,31,31,22,10};
    

	t_filter instantiated_filter;  //instantiation of the filter

   //initialize the variables for filter main process 
	t_in  d_in;  
	t_acc d_out;

    //get the input to the filter
	d_in = in.read();
	//executes the main process of the filter
	instantiated_filter.process(d_in,coef, &d_out);
	//outputs the result of the filtering
    out.write(d_out);
}

/*

void filter_std(hls::stream<sp_filter_std::t_in> & in, hls::stream<sp_filter_std::t_acc> & out)
{
	t_in signal_in;
	t
}
template<filter_mode mode, typename t_data, typename t_coef, typename t_acc, int size>
*/