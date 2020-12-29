/*
 * =====================================================================================
 *
 *       Filename:  hls.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/11/2020 08:47:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathieu LEBON (ML), mathieu.lebon@thalesaleniaspace.com
 *   Organization:  Thales Alenia Space
 *
 * =====================================================================================
 */

#ifndef __HLS__
#define __HLS__

// sudo apt remove libgmp-dev

#ifndef __SYNTHESIS__
// ------------------------------------
// !! Vivado BUG !! (Adapt the path)
// ------------------------------------
// #include "/tools/Xilinx/Vivado/2019.1/include/gmp.h"
//#include "/home/accesscore/soft/xilinx/Vitis_HLS/2020.2/include/gmp.h"
// ------------------------------------
#include  <cstdlib>
#include  <fstream>
#include  <iomanip>   
#include  <sstream>  
#include  <iostream>  
using namespace std;
#endif

#include <ap_int.h>
#include <hls_stream.h>
//#include <complex>
#include "c_complex.h"

#ifdef __SYNTHESIS__
#undef assert
#define assert(x)
#endif

#endif

