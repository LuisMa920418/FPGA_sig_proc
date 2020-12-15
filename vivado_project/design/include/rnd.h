// =====================================================================================
// 
//       Filename:  rnd.h
// 
//    Description:  clip / round / trunc
// 
//        Version:  1.1
//       Revision:  1.1 - support hls_int type + lsb_delete parameter
//       Compiler:  g++
// 
//         Author:  Mathieu Lebon (ML), 
//        Company:  Thales Alenia Space
// 
// =====================================================================================
// =====
// TO DO
// =====
//
// - Add complex types
//
// =========
// Functions
// =========
//
// - clip
// - rnd
// - rnd_clip
// - trunc
// - trunc_clip
// - custom_rnd
// - custom_rnd_clip
//
// ========
// Examples
// ========
//
//   using namespace sp_rnd;        // Indicates the namespace
//
//   int10 in;
//   int5  out;
//
//  --------
//  | clip |
//  --------
//
//   clip(in,out);
//
//  -------
//  | rnd |
//  -------
//
//  rnd(in,out);
//  rnd<1>(in,out);                 // Supprime 1 LSB;
//
//  rnd_clip(in,out);
//  rnd_clip<1>(in,out);            // Supprime 1 LSB;
//
//  ---------
//  | trunc |
//  ---------
//
//  trunc(in,out);
//  trunc<1>(in,out);               // Supprime 1 LSB;
//
//  trunc_clip(in,out);
//  trunc_clip<1>(in,out);          // Supprime 1 LSB;
//
//  --------------
//  | custom_rnd |
//  --------------
//
//  custom_rnd<VAL>(in,out);
//  custom_rnd<VAL,1>(in,out);      // Supprime 1 LSB;
//  custom_rnd_clip<VAL>(in,out);
//  custom_rnd_clip<VAL,1>(in,out); // Supprime 1 LSB;
//
//  Note : VAL = AC_TRN         => trunc towards -inf
//               AC_TRN_ZERO    => trunc towards 0
//               AC_RND         => round towards +inf
//               AC_RND_ZERO    => round towards 0
//               AC_RND_INF     => round towards +/- inf
//               AC_RND_MIN_INF => round towards -inf
//               AC_RND_CONV    => round towards even q multiples
//
// =====================================================================================

#include <ap_fixed.h>

#ifndef __RND__
#define __RND__

#ifdef __SYNTHESIS__
#undef  assert
#define assert(x)
#endif

//#define __BYPASS_RND__

namespace sp_rnd {

  //====================================================================================
  // ROUND / TRUNC
  // OUTPUT_QUAN : Output word quantization : AC_TRN  (default), AC_TRN_ZERO, AC_RND, AC_RND_ZERO, AC_RND_INF, AC_RND_MIN_INF, AC_RND_CONV
  // OUTPUT_OVER : Output word overflow    : AC_WRAP (default), AC_SAT, AC_SAT_ZERO, AC_SAT_SYM
  //====================================================================================

  template < int LSB_DELETE_MAX, ap_q_mode OUTPUT_QUAN, ap_o_mode OUTPUT_OVER, typename t_in, typename t_lsb_del, typename t_out >
    inline void rnd_base( t_in in, t_lsb_del lsb_delete, t_out & out) {
#ifdef __BYPASS_RND__
      out = in;
#else
      typedef ap_fixed<t_in::width,t_in::width>                                t_input; // avoid modelsim bug
      typedef ap_fixed<t_in::width+LSB_DELETE_MAX,t_in::width,AP_TRN,AP_WRAP> t_fixed_lsb;
      typedef ap_fixed<t_out::width,t_out::width,OUTPUT_QUAN,OUTPUT_OVER>     t_fixed_rnd;

      t_input input = in;
      t_fixed_lsb a = input;
      t_fixed_rnd b = a >> lsb_delete;

      out = b.to_int();//.to_ap_int();
#endif
    }

  template < int LSB_DELETE, ap_q_mode OUTPUT_QUAN, ap_o_mode OUTPUT_OVER, typename t_in, typename t_out >
    inline void rnd_base(t_in in, t_out & out) {
      rnd_base<LSB_DELETE,OUTPUT_QUAN,OUTPUT_OVER>(in,LSB_DELETE,out);
    }

  // Clip / rnd / trunc ------------------------------------------------

#define OP1(op,mode1,mode2)                                                                                                 \
  template <int LSB_DELETE, typename t_in, typename t_out>                                                                 \
    inline void op(t_in in, t_out & out) { rnd_base<LSB_DELETE,mode1,mode2>(in,out); }                                     \
                                                                                                                           \
  template <int LSB_DELETE_MAX, typename t_in, typename t_lsb_del, typename t_out>                                         \
    inline void op(t_in in, t_lsb_del lsb_delete, t_out & out) { rnd_base<LSB_DELETE_MAX,mode1,mode2>(in,lsb_delete,out); }\
                                                                                                                           \
  template <typename t_in, typename t_out>                                                                                 \
    inline void op(t_in in, t_out & out) { rnd_base<0,mode1,mode2>(in,out); }

  // -------------------------------------------------------------------

  OP1(clip,AP_TRN,AP_SAT)
  OP1(rnd,AP_RND_INF,AP_WRAP)
  OP1(rnd_clip,AP_RND_INF,AP_SAT)
  OP1(trunc,AP_TRN,AP_WRAP)
  OP1(trunc_clip,AP_TRN,AP_SAT)

  // Custom ------------------------------------------------------------

#define OP2(op,mode)                                                                                                            \
  template < ap_q_mode OUTPUT_QUAN, int LSB_DELETE, typename t_in, typename t_out>                                              \
    inline void op(t_in in, t_out & out) { rnd_base<LSB_DELETE,OUTPUT_QUAN,mode>(in,out); }                                     \
                                                                                                                                \
  template <ap_q_mode OUTPUT_QUAN, int LSB_DELETE_MAX, typename t_in, typename t_lsb_del, typename t_out>                       \
    inline void op(t_in in, t_lsb_del lsb_delete, t_out & out) { rnd_base<LSB_DELETE_MAX,OUTPUT_QUAN,mode>(in,lsb_delete,out); }\
                                                                                                                                \
  template <ap_q_mode OUTPUT_QUAN, typename t_in, typename t_out>                                                               \
    inline void op(t_in in, t_out & out) { rnd_base<0,OUTPUT_QUAN,mode>(in,out); }

  // -------------------------------------------------------------------

  OP2(custom_rnd,AP_WRAP)
  OP2(custom_rnd_clip,AP_SAT)

  // -------------------------------------------------------------------

#define OP_FUNC(x)                                                          \
  template<int LSB_DELETE_MAX = 0>                                          \
  struct op_##x {                                                           \
    template<typename t_in, typename t_out>                                 \
      inline void operator() (t_in in, t_out & out) {                       \
        x<LSB_DELETE_MAX>(in,out);                                          \
      }                                                                     \
    template<typename t_in, typename t_lsb_del, typename t_out>             \
      inline void operator() (t_in in, t_lsb_del lsb_delete, t_out & out) { \
        x<LSB_DELETE_MAX>(in,lsb_delete,out);                               \
      }                                                                     \
  };

  // -------------------------------------------------------------------

  OP_FUNC(clip)
  OP_FUNC(rnd)
  OP_FUNC(rnd_clip)
  OP_FUNC(trunc)
  OP_FUNC(trunc_clip)
  
  struct nop {
    template<typename t_in, typename t_out>
      void operator() (t_in in, t_out & out) {
        out = in;
      }
  };
};

#endif

