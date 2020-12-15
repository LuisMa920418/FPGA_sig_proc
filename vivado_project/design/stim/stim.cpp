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

#include "stim.h"

namespace sp_stim {

	void top(ac_channel<t_out> & out) {

		for(int i=0; i<512; i++) {
			out.write(stim_ref[i]);
		}
	}

};

