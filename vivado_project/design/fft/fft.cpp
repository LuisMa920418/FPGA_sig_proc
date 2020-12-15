// =====================================================================================
// 
//        @file   fft.cpp
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

#include "fft.h"

using namespace sp_fft;

void fft(hls::stream<t_in> & in, t_data_mem mem_out[64]) {

	static const t_coef coef[] =
	{
		t_coef(2047,0),
		t_coef(2037,-201),
		t_coef(2008,-399),
		t_coef(1959,-594),
		t_coef(1891,-783),
		t_coef(1805,-965),
		t_coef(1702,-1137),
		t_coef(1582,-1299),
		t_coef(1447,-1447),
		t_coef(1299,-1582),
		t_coef(1137,-1702),
		t_coef(965,-1805),
		t_coef(783,-1891),
		t_coef(594,-1959),
		t_coef(399,-2008),
		t_coef(201,-2037),
		t_coef(0,-2047),
		t_coef(-201,-2037),
		t_coef(-399,-2008),
		t_coef(-594,-1959),
		t_coef(-783,-1891),
		t_coef(-965,-1805),
		t_coef(-1137,-1702),
		t_coef(-1299,-1582),
		t_coef(-1447,-1447),
		t_coef(-1582,-1299),
		t_coef(-1702,-1137),
		t_coef(-1805,-965),
		t_coef(-1891,-783),
		t_coef(-1959,-594),
		t_coef(-2008,-399),
		t_coef(-2037,-201)
	};

	// ...
}

