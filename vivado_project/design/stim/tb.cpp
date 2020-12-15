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

#include "tb.h"

namespace sp_stim {

	void test_top(ac_channel<t_out> & out) {
		CCS_DESIGN(top)(out);
	}

};

// =========================================================================

CCS_MAIN(int argc, char **argv)
{
	ac_channel<t_out> out;

	test_top(out);

	cout << "\n\n[STIM]\n\n";

	for(int i = 0; i<512; i++) {
		cout << out.read() << endl;
	}

	CCS_RETURN(0) ;
}

// =========================================================================

