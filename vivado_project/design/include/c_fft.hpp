// =====================================================================================
// 
//       Filename:  c_fft.hpp
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

#ifndef __C_FFT__
#define __C_FFT__

//#include "mentor/ac_int.h"
#include "rnd.h"
using namespace sp_rnd;

// =====================================================================================
//        Class:  c_fft
//  Description:  
// =====================================================================================

template<int size, typename t_data_mem, typename t_coef, int butterfly_lsb_delete>
class c_fft {

  t_data_mem mem[size];

	// ------------------------
	// !! VIVADO BUG (again) !!
	// ------------------------
  // static const int size_log2 = ac::log2_ceil<size>::val;
	// Temporary workaround :
  static const int size_log2 = 6;
	// ------------------------
  static const int size_div2 = size/2;

  typedef c_complex<ap_int<32> > t_data_mult;
  typedef ap_uint<size_log2>     t_addr;

  public:

	// ------------------------------------------------
	// No internal memory initialization
	// ------------------------------------------------

	c_fft() {
		// ...
	}

  // -----------------------------------------------------
  // Bit reverse
  // -----------------------------------------------------

	template<int qt>
	ap_uint<qt> bit_reverse(ap_uint<qt> x) {
		// ...
	}

  // -----------------------------------------------------
  // Read input channel and write data to process memory
  // -----------------------------------------------------

  template<typename t_chan>
    void read(t_chan & in) {
			// Bit reverse read
			// ...
    }

  // -----------------------------------------------------
  // Copy result memory to output memory
  // -----------------------------------------------------


	void write(t_data_mem * mem_out) {
		// ...
	}


  void process(const t_coef * coef) {

    ap_int<32> mask1 = 0;
    ap_int<32> mask2 = - 1;
    ap_int<32> mask3 = 1;
    ap_int<32> temp1;
    ap_int<32> temp2;
    ap_int<32> index_low;    
    ap_int<32> index_high;
    ap_int<32> n2 = size;
    ap_int<32> index_coef;

    //################## STAGES LOOP ##################

STAGE_LOOP:
    for (int i=0; i<size_log2; i++) {

      n2 = n2 >> 1; 
      index_coef = 0;

      //################## BUTTERFLY LOOP ##################

BUTTERFLY_LOOP:
      for (int j=0; j<size_div2; j++) {
#pragma HLS pipeline II=1

        // Update data address

        temp1      = j & mask1;
        temp2      = (j & mask2) << 1;
        index_low  = temp1     | temp2;
        index_high = index_low | mask3;

        // Memory Read

        t_data_mem  data_high = mem[index_high];
        t_data_mem  data_low  = mem[index_low];
        t_coef      data_coef = coef[index_coef];

        t_data_mem x;
        t_data_mem y;

        butterfly(data_high,data_low,data_coef,x,y);

        // Memory write

        mem[index_high] = x;
        mem[index_low]  = y; 

        // Update coef address

        if (i != 0 ) {
          index_coef = index_coef + n2;
          if (index_coef == size_div2) index_coef = 0; 
        }
      }

      mask1 += mask3;
      mask2 = mask2 << 1;
      mask3 = mask3 << 1; 
    }
  }

  void butterfly(t_data_mem data_high, t_data_mem data_low, t_coef coef, t_data_mem & res_high, t_data_mem & res_low) {

    t_data_mult data_mult = mult(data_high,coef);

    // Sum

    res_high.real = data_low.real - data_mult.real;
    res_high.imag = data_low.imag - data_mult.imag;
    res_low.real  = data_low.real + data_mult.real;
    res_low.imag  = data_low.imag + data_mult.imag;

  }

  t_data_mult mult(t_data_mem data, t_data_mem coef) {

    ap_int<32> a_mult,    b_mult,    c_mult,    d_mult;
    ap_int<32> a_mult_rc, b_mult_rc, c_mult_rc, d_mult_rc;

    // Multiplication

    a_mult = data.real * coef.real;
    b_mult = data.imag * coef.imag;
    c_mult = data.real * coef.imag;
    d_mult = data.imag * coef.real;

    // Round

    rnd<butterfly_lsb_delete>(a_mult, a_mult_rc);
    rnd<butterfly_lsb_delete>(b_mult, b_mult_rc);
    rnd<butterfly_lsb_delete>(c_mult, c_mult_rc);
    rnd<butterfly_lsb_delete>(d_mult, d_mult_rc);

    // Partial sum

    t_data_mult res;
    res.real = (a_mult_rc - b_mult_rc);
    res.imag = (c_mult_rc + d_mult_rc);

    return res;
  }

}; // -----  end of class c_fft  -----


#endif


