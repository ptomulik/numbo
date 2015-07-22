// @COPYRIGHT@
// Licensed under MIT license (LICENSE.txt)

// numbo/opencl/program_generator.t.h

/** // doc: numbo/opencl/program_generator.t.h {{{
 * \file numbo/opencl/program_generator.t.h
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_OPENCL_PROGRAM_GENERATOR_T_H_INCLUDED
#define NUMBO_OPENCL_PROGRAM_GENERATOR_T_H_INCLUDED

#include <cxxtest/TestSuite.h>
#include <numbo/opencl/program_generator.hpp>
#include <clxx/cl/platform_layer.hpp>

/** \cond DOXYGEN_SHOW_UNIT_TESTS */
namespace numbo { namespace opencl { class program_generator_test_suite; } }

class numbo::opencl::program_generator_test_suite : public CxxTest::TestSuite
{
  clxx::context new_context(clxx::device_type_t dev_type = clxx::device_type_t::all) const
  {
    clxx::platform_layer platform_layer{ dev_type };
    clxx::platform platform{ platform_layer.get_platforms()[0] };
    return clxx::context(clxx::make_context_properties(), platform_layer.get_devices(platform));
  }
public:
  void test__trivial_generator__1( )
  {
    class trivial_generator
      : public program_generator
    {
      void generate_source(clxx::program_source& src) const
      {
        generate_line_directive(src, 1);
        src.append("__kernel void trivial() { }\n");
      }
      std::string program_name() const
      { return "trivial"; }
    };

    program_generator const& g = trivial_generator();
    clxx::context c{new_context()};
    clxx::program p1{ g.get_program(c) };
    clxx::program p2{ g.get_program(c) };
    TS_ASSERT(p1 == p2); // it should be same handle...
  }
};
/** \endcond */

#endif /* NUMBO_OPENCL_PROGRAM_GENERATOR_T_H_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
