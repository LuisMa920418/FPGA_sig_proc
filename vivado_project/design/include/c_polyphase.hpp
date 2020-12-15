// =====================================================================================
// 
//       Filename:  c_polyphase.hpp
// 
//    Description:  
// 
//        Version:  1.0
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Mathieu Lebon (ML), 
//        Company:  Thales Alenia Space
// 
// =====================================================================================

#ifndef __C_POLYPHASE__
#define __C_POLYPHASE__

#include "hls.h"
#include "c_filter.hpp"
#include "rnd.h"

using namespace sp_rnd;

// =====================================================================================
//        Class:  c_polyphase
//  Description:  
// =====================================================================================

template<int size, typename t_data, typename t_coef, typename t_acc, int shift, typename t_out>
class c_polyphase {

	enum {
		nb_branch   = 2,
		size_filter = size/nb_branch
	};

	// Branch 1 : Symmetric filter
	// Branch 2 : Standard filter

	// ...
	// ...

	t_acc d_acc_poly;
	int   cpt;

	public:

	c_polyphase() {
		cpt = 0;
		d_acc_poly = 0;
	}

	void process(hls::stream<t_data> & in, const t_coef *coef_1, const t_coef *coef_2, hls::stream<t_out> & out ) {

		t_data d_in;
		t_acc  d_acc_filter;
		t_out  d_out;

		d_in = in.read();

		// ...

		// ------------------------------------------------------
		// Function : "d_out = round(d_acc_poly)"
		// Variable : "d_out" is the polyphase output data
		// Variable : "d_acc_poly" is the polyphase accumulator
		// ------------------------------------------------------

		rnd<shift>(d_acc_poly.real,d_out.real);
		rnd<shift>(d_acc_poly.imag,d_out.imag);

		// --------------
		// Write output 
		// --------------

		if(cpt==nb_branch-1) {

			// ...

		} else {
			cpt++;
		}

	}

}; // -----  end of class polyphase  -----

#endif

