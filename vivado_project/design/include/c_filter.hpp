// =====================================================================================
// 
//       Filename:  c_filter.hpp
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

#ifndef __C_FILTER__
#define __C_FILTER__

enum filter_mode {
	standard,
	symmetric
};

// =====================================================================================
//        Class:  c_filter
//  Description:
//
//  mode   = standard or symmetric
//  t_data = type of filter input data
//  t_acc  = type of filter accumulator
//  size   = Number of taps
//
// =====================================================================================

template<filter_mode mode, typename t_data, typename t_coef, typename t_acc, int size>
class c_filter {

	//when the filter is symetric what's the format of the coeficients in the vector coef?
	//for a filter symetric having coeficients 1 2 3 2 1 
	//Option 1  coef = 1 2 3 2 1 , thus size = 5
	//Option 2  coef =  1 2 3 , thus size 3
	//Option 3  coef = 1 2 3 size = 5


	static const int size_div2 = size/2; // Number of taps divided by 2

	t_data reg[size];                    // TAPS

	t_acc  acc;                          // Accumulator

	public:

	// ------------------------------------------------
	// TAPS registers initialization
	// Reset TAPS to 0
	// ------------------------------------------------

	void reset() {
		acc = 0;  //clear accumulator
		for(int i=0;i<size;i++) {
		reg[i] = 0; //clear internal registers
		}
	}

//contructor of the class c_filter
	c_filter() {
		
		reset();

	}

	// ------------------------------------------------
	// Filter main process
	// ------------------------------------------------

	void process(t_data in, const t_coef *coef, t_acc & out) {

		acc = 0;
		shift(in);
		if(mode == symmetric) {
			mac_sym(coef);
		} else {
			mac(coef);
		}
		out = acc; //assigning out here or inside  #to check
	}

	private :

	// ------------------------------------------------
	// Shift TAPS registers
	// ------------------------------------------------

	void shift(t_data in) {
		
		for(int i=size-1;i>0;i--) {
		reg[i] = reg[i-1]; //clear internal registers
		}
		reg[0] = in;
	}

	// ------------------------------------------------
	// Multiply Accumulate for symmetric filter
	// ------------------------------------------------
	// !!! VIVADO BUG !!!
	// use "mult_add(a,b,c)" instead of "c += a * b"
	// ------------------------------------------------

	void mac_sym(const t_coef *coef) {
		//size_div2
	  for (int i = 0; i <size_div2-1 ; i++)
		 {
		   mult_add(reg[size-1-i]+reg[i], coef[i], acc);
		 }
		  //for odd sizes  another addition is missing i the previous for loop
     if (size%2==1)
	 { 		
		 mult_add(reg[size_div2], coef[size_div2], acc);
	 }
	 
	}

	// ------------------------------------------------
	// Multiply Accumulate for standard filter
	// ------------------------------------------------
	// !!! POSSIBLE VIVADO BUG (depends on version) !!!
	// use "mult_add(a,b,c)" instead of "c += a * b"
	// ------------------------------------------------

	void mac(const t_coef *coef) {

         for (int i = 0; i < size ; i++)
		 {
            mult_add(reg[i], coef[i], acc);
		 }

	}

	// ------------------------------------------------
	// mult_add(a,b,c) => c += a * b
	// ------------------------------------------------

	template<typename t1, typename t2, typename t3>
		void mult_add(t1 a, t2 b, t3 & c) {
			t3 m;
			//#pragma HLS RESOURCE variable=m core=Mul
			// m = a * b;
			m.real = a.real * b;
			m.imag = a.imag * b;
			c += m;
		}

}; // -----  end of class c_filter  -----

#endif


