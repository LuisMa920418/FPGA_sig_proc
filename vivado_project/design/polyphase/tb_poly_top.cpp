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
#include "poly_top.h"
#include "c_compare.h"
#include "reference.h"

using namespace sp_poly_top;
using namespace std;

int main(int argc, char **argv)
{
	hls::stream<t_in>  in;
	hls::stream<t_out> out;

	for ( int i = 0; i < 512; i += 1 ) {
		in.write(ref_input[i]);
	}

	while(in.size()) {
		poly_top(in,out);
	}

	cout << "\n\n[TOP POLYPHASE]\n\n";

	c_compare cmp;
	return cmp.chan(out,ref_poly_top);
}

