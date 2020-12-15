// =====================================================================================
// 
//       Filename:  filter_std.h
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

#ifndef __FILTER_STD__
#define __FILTER_STD__

#include "hls.h"
#include "c_filter.hpp"

namespace sp_filter_std {

  typedef c_complex<ap_int<10> > t_in;
  typedef c_complex<ap_int<21> > t_acc;
  typedef ap_int<11>                t_coef;

  static const int filter_size = 6; 

  typedef c_filter<standard,t_in,t_coef,t_acc,filter_size> t_filter;

 class c_accu
 {
   public:
    int  N //number of accumulations
    //t_in T_data; //input data type
    t_acc  buffer; // accumulator buffer type, or output type


 

  void process(hls::stream<t_in> & in, hls::stream<t_acc> & out)
  {
    /*ASKKKKK Must we have into account that the data is complex when doind the 
    operations??*/


      buffer = 0;
      for (int i = 0; i < N; i++)
      {
        buffer +=  in.read();
      }
      out.write(buffer);
  }
   
 };
 

 class multiplier
 {
   // public:
  // t_in A,B;//inputs to the multiplier attributes?
   //t_acc product; //result of the multiplication
  
     
     void process(hls::stream<t_in> & in1,hls::stream<t_in> & in2, hls::stream<t_acc> & out)
     {
       //A = in1.read();
       //B= in2.read();
      // product =  A * B;
       
       out.write(in1.read() * in2.read());
     }
    
 };
 
 

 

};

void filter_std(hls::stream<sp_filter_std::t_in> & in, hls::stream<sp_filter_std::t_acc> & out);

#endif

