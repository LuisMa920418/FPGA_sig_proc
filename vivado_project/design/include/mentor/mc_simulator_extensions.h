#ifndef MC_SIMULATOR_EXTENSIONS_H_INC
#define MC_SIMULATOR_EXTENSIONS_H_INC

#include <systemc.h>

/*! \file This header defines a common interface to the systemc
 *  extensions of the various simulators used by the verification
 *  flow.
 */

#if defined MTI_SYSTEMC

#define MC_SIMULATOR_MSIM
#define MC_MODULE_EXPORT(classname) SC_MODULE_EXPORT(classname)

typedef sc_foreign_module mc_foreign_module;

#elif defined NCSC

#define MC_SIMULATOR_NCSIM
#define MC_MODULE_EXPORT(classname) NCSC_MODULE_EXPORT(classname)

class mc_foreign_module : public ncsc_foreign_module {
public:
  mc_foreign_module(const sc_module_name& name, const char* hdl_name)
    : ncsc_foreign_module(name)
    , _hdl_name(hdl_name)
  {}

  virtual const char* hdl_name() const { return _hdl_name.c_str(); }

private:
  std::string _hdl_name;
};

#elif defined VCS_SYSTEMC

extern "C" bool hdl_elaboration_only();

#define MC_SIMULATOR_VCS
#define MC_MODULE_EXPORT(classname)

#ifndef CCS_DUT_SYSC
// If not building with SystemC DUT from Catapult, then 
// include the SystemC wrapper created by vhdlan/vlogan

// If Catapult SystemC-based design, ensure that wrapper is placed in namespace for SCVerify
#ifdef CCS_VCS_NAMESPACE
namespace CCS_VCS_NAMESPACE {
#endif

#define VCS_QUOTE_HDR(x) VCS_QUOTE_HDR1(x.h)
#define VCS_QUOTE_HDR1(x) #x
#include VCS_QUOTE_HDR(TOP_HDL_ENTITY)

#ifdef CCS_VCS_NAMESPACE
}
#define CCS_SCOPED_HDL CCS_VCS_NAMESPACE::TOP_HDL_ENTITY
#else
#define CCS_SCOPED_HDL TOP_HDL_ENTITY
#endif

// Synopsys VCS SystemC
class mc_foreign_module : public CCS_SCOPED_HDL {
public:
  mc_foreign_module(const sc_module_name& name, const char* hdl_name)
    : TOP_HDL_ENTITY(name)
    , _hdl_name(hdl_name)
  {}

  virtual const char* hdl_name() const { return _hdl_name.c_str(); }

private:
  std::string _hdl_name;
};

#endif

#else // OSCI

#define MC_SIMULATOR_OSCI
#define MC_MODULE_EXPORT(classname)

// no definition for mc_foreign_module

#endif


#endif // MC_SIMULATOR_EXTENSIONS_H_INC
