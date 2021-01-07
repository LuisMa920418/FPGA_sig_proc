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
#include "polyphase_3.h"
#include "c_compare.h"
#include "reference.h"

using namespace sp_poly_3;
using namespace std;

int main(int argc, char **argv)
{
		hls::stream<t_in>  in;
		hls::stream<t_out> out;

		for ( int i = 0; i < 50; i += 1 ) {
			t_in d(i,i%10);
			in.write(d);
		}

		while(in.size())  
		poly_3(in,out);

		cout << "\n\n[FILTER POLY_3]\n\n";

		c_compare cmp;
	return cmp.chan(out,ref_poly_3);

}
	// =========================================================================

