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
#include "filter_std.h"
#include "c_compare.h"
#include "reference.h"

using namespace sp_filter_std;
using namespace std;

int main(int argc, char **argv)
{
	hls::stream<t_in>  in;
	hls::stream<t_acc> out;

	for ( int i = 0; i < 50; i += 1 ) {
		t_in d(i,i%10);
		in.write(d);
	}

	while(in.size())
	filter_std(in,out);

	cout << "\n\n[FILTER STD]\n\n";

	c_compare cmp;
	return cmp.chan(out,ref_filter_std);
}

