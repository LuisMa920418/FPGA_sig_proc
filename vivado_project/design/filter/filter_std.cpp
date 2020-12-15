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
	// ...

	t_in  d_in;
	t_acc d_out;

	// ...

/*
	for(j = 0;j < size+size_filter;j++)
{
  output[j] = 0;
  for(i = 0;i < size_filter;i++)
  {         

    output[j] += buffer[i]*filter[j-i];
  }
}
*/
}



void filter_std(hls::stream<sp_filter_std::t_in> & in, hls::stream<sp_filter_std::t_acc> & out)
{
	t_in signal_in;
	t
}
