#ifndef MC_SCVERIFY_H_INC
#define MC_SCVERIFY_H_INC
//
// mc_scverify.h
//
// This header file provides macros useful for creating testbenches
// for standard C++ designs as well as SystemC testbenches.
// Support for either standard C++ or SystemC is controlled by
// the compiler directive '#ifdef CCS_SYSC'.
//

#if defined(CCS_SYSC) && !defined(CCS_SCVERIFY)
//---------------------------------------------------------
// SystemC testbench mode
//
// Verification with SystemC testbenches requires that the
// testbench be self-checking and that it return a non-zero
// exit code to signal failure.
//
// A sample SystemC testbench (and sc_main) look like this:
//
// TBD
//
// SC_MODULE(testbench)
// {
// public:
//   // Interconnect
//   sc_in_clk               clk;
//   sc_signal<bool>         rst;
//   sc_signal<int>          datain;
//   sc_signal<int>          dataout;
//
//   // Design Under Test (DUT)
//   CCS_DESIGN(adder) adder_INST;
//
//   SC_CTOR(testbench) 
//     : adder_INST("adder_INST")
//     , rst("rst"), datain("datain"), dataout("dataout") {
//   }
//
//   // ... BODY OF TESTBENCH GOES HERE. Create methods
//   // to drive inputs and check outputs. Mismatches
//   // should increment '_error_count'.
//
//   unsigned get_error_count() { return _error_count; }
// private:
//   unsigned _error_count;
// };
//
// int sc_main(int argc, char *argv[])
// {
//   sc_clock clk("clk", 10, SC_NS, 0.5, 0, SC_NS, 0);
//   testbench testbench_INST("testbench_INST");
//   testbench_INST.clk(clk);
//   sc_start();
//   return testbench_INST.get_error_count();
// }

#undef CCS_DESIGN
#define CCS_DESIGN(a) CCS_RTL::a

#ifndef SC_USE_STD_STRING
#define SC_USE_STD_STRING
#endif

#ifndef SC_INCLUDE_DYNAMIC_PROCESSES
#define SC_INCLUDE_DYNAMIC_PROCESSES
#endif

// Include transactor models
#include <mc_scv_trans.h>

#else

#if !defined(CCS_SYSC) && defined(CCS_SCVERIFY)
//---------------------------------------------------------
// Standard C++ testbench mode
//
// For standard C++ design testbenches, this file provides macros to 
// simplify the creation of C++ testbench files that are SCVerify-ready.
//
// A sample testbench file looks like this:
//
// #include "mc_scverify.h"
// // Include C++ design function
// #include "my_func.h"
//
// CCS_MAIN(int argc, char *argv[])
// {
//   for (int iteration=0; iteration<5; iteration++) {
//      int arg1 = iteration;     // 1st arg to my_func
//      int arg2 = iteration+1;   // 2nd arg to my_func
//      int arg3;                 // result
//      CCS_DESIGN(my_func)(arg1,arg2,&arg3);
//      cout << arg3 << endl;
//   }
//   return 0;  // return success
// }

#undef CCS_DESIGN
#undef CCS_MAIN
#undef CCS_RETURN

#define CCS_RETURN(a) return(a)
#define CCS_DESIGN(a) testbench::exec_##a
#define CCS_MAIN(a,b) int testbench::main()
#include <mc_testbench.h>

#else
//---------------------------------------------------------
// No special verification mode
#define CCS_DESIGN(a) a
#define CCS_MAIN(a,b) int main(a,b)
#define CCS_RETURN(a) return(a)

#endif

#endif

#endif

