// =====================================================================================
// 
//       Filename:  tb.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Mathieu Lebon
//      Reference:  
//        Company:  Thales Alenia Space
// 
// =====================================================================================

#include "hls.h"
#include "fft.h"
#include "c_compare.h"
#include "reference.h"

using namespace sp_fft;

int main(int argc, char **argv)
{
	hls::stream<t_in>  in;
	t_data_mem mem_out[64];

	for ( int i = 0; i < 64; i += 1 ) {
		in.write(ref_poly_3[i]);
	}

	fft(in,mem_out);

	c_compare cmp;

#if 1
	// Check with bit reverse (expected one)
	return cmp.array(mem_out,ref_fft_rev,64);
#else
	// Check without bit reverse (debug)
	return cmp.array(mem_out,ref_fft,64);
#endif
}

// =========================================================================

