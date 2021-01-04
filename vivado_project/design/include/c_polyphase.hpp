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
		nb_branch   = 2,  // #toask is thuis the decimation factor? 
		size_filter = size/nb_branch
	};
   

	

		// nb_branch = 1 : 2 Symmetric filters  having coef from coef1 and coef2
		c_filter<symmetric,t_data,t_coef,t_acc,size_filter> instance_filter_sym_branch1;//instance for symetric filter

		 // nb_branch =  2 : Standard filter  // #toask is the standard filter going to be used???
    c_filter<standard,t_data,t_coef,t_acc,size_filter> instance_filter_std;    //instance for std filter
	
   
	t_acc d_acc_poly;
	int   cpt; //compteur

	public:

	c_polyphase() {
		cpt = 0;
		d_acc_poly = 0;
	}

	void process(hls::stream<t_data> & in, const t_coef *coef_1, const t_coef *coef_2, hls::stream<t_out> & out ) {

		t_data d_in;
		t_acc  d_acc_filter;
		t_out  d_out;
        

       /*
	   cpt in range 0 to 1-> case two branches
	   cpt always 0 -> case one branch 
	   */
		
		
		d_in = in.read();
        
         //case polyphase with two branches
			if (cpt==0)
			{
				instance_filter_sym_branch1.process(d_in,coef_1, d_acc_filter);
			}
			else
			//case cpt ==1
			{
				/*
				#toask is this equivalent for the filter using coef_2?
				instance_filter_branch2.shift(d_in);  //store the data
				int size_div2 = instance_filter_branch2.size_div2; //get the constant size_div2
				//get the data
				t_data a =instance_filter_branch2.reg[size_div2];  
				//get the coeficient
				t_data b = coef_2[size_div2]; 
				int coef_int = b.to_int();
				//get the number of shifting
				shift_times = log2(coef_int);  //how to get this??
				//mshift
				d_acc_filter.real = a.real<<shift_times;
				d_acc_filter.imag = a.imag<<shift_times;
*/
				instance_filter_std.process(d_in,coef_2,d_acc_filter);
			}
			d_acc_poly +=d_acc_filter;



	
		
        
		

		// ------------------------------------------------------
		// Function : "d_out = round(d_acc_poly)"
		// Variable : "d_out" is the polyphase output data
		// Variable : "d_acc_poly" is the polyphase accumulator
		// ------------------------------------------------------


	 //shift right "shift" times(divission by 2^"shift"), d_acc_poly and store the return int value in d_out
	 //sum(abs(filter_coefficients))=1286~=2^10 = 1024
	 //is this shifting the unity gain filter conversion??(fir filter with integer values) 
		rnd<shift>(d_acc_poly.real,d_out.real); 
		rnd<shift>(d_acc_poly.imag,d_out.imag);

		// --------------
		// Write output 
		// --------------

		if(cpt==nb_branch-1) {

			
			d_acc_poly=0;
			out.write(d_out);
			cpt=0;

		} else {
			cpt++;
		}

	}

}; // -----  end of class polyphase  -----

#endif

