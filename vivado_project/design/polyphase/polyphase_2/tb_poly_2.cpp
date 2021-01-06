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
#include "polyphase_2.h"
#include "c_compare.h"
#include "reference.h"

using namespace sp_poly_2;
using namespace std;

int main(int argc, char **argv)
{

	hls::stream<t_in>  in;
	hls::stream<t_out> out;

	//store 50 values into the FIFO "in", input data
		for ( int i = 0; i < 50; i += 1 ) {
			t_in d(i,i%10);
			in.write(d);
		}

 //filter all the values inside "in" as long as there is data in the FIFO
   //in.size()=0 means the FIFO is empty 
	while(in.size())  
	poly_2(in,out); //"out" is size(in)/2 because it has been downsampled by 2

//printing results,
	cout << "\n\n[FILTER POLY_2]\n\n";

//print and compare the data result from "out" test filter versus "ref_poly_1"
	c_compare cmp;
	return cmp.chan(out,ref_poly_2);


}

