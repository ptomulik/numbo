// @COPYRIGHT@
// Licensed under MIT license (LICENSE.txt)

// numbo/opencl/static_program_generator.t.h

/** // doc: numbo/opencl/static_program_generator.t.h {{{
 * \file numbo/opencl/static_program_generator.t.h
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_OPENCL_STATIC_PROGRAM_GENERATOR_T_H_INCLUDED
#define NUMBO_OPENCL_STATIC_PROGRAM_GENERATOR_T_H_INCLUDED

#include <cxxtest/TestSuite.h>
#include <numbo/opencl/static_program_generator.hpp>

/** \cond DOXYGEN_SHOW_OPENCL_STATIC_PROGRAM_GENERATOR_TESTS */
namespace numbo { namespace opencl { class static_program_generator_test_suite; } }

class numbo::opencl::static_program_generator_test_suite : public CxxTest::TestSuite
{
  class G0 : public static_program_generator<G0>
  {
    typedef static_program_generator<G0> Base;
  public:
    inline static size_t
    static_estimated_program_size(clxx::context const&)
    { return 160ul; }
    inline static std::string const&
    static_program_name()
    {
      static const std::string s{"g0"};
      return s;
    }
    inline static std::string const&
    static_program_file()
    {
      static const std::string s{"g0.cl"};
      return s;
    }
    void generate_program_body(std::string& src, clxx::context const&) const
    { src.append("__kernel void trivial() { }\n"); }
  };
public:
  // static methods
  void test__static_program_namespace__1( )
  {
    TS_ASSERT_EQUALS(G0::static_program_namespace(), "numbo::opencl::programs");
  }
  void test__static_program_name__1( )
  {
    TS_ASSERT_EQUALS(G0::static_program_name(), "g0");
  }
  void test__static_program_full_name__1( )
  {
    TS_ASSERT_EQUALS(G0::static_program_full_name(), "numbo::opencl::programs::g0");
  }
  void test__static_program_file_suffix__1( )
  {
    TS_ASSERT_EQUALS(G0::static_program_file_suffix(), ".cl");
  }
  void test__static_program_file__1( )
  {
    TS_ASSERT_EQUALS(G0::static_program_file(), "g0.cl");
  }
  void test__static_program_dir__1( )
  {
    TS_ASSERT_EQUALS(G0::static_program_dir(), "numbo/opencl/programs");
  }
  void test__static_program_path__1( )
  {
    TS_ASSERT_EQUALS(G0::static_program_path(), "numbo/opencl/programs/g0.cl");
  }
  void test__static_estimated_program_size__1( )
  {
    clxx::context c;
    TS_ASSERT_EQUALS(G0::static_estimated_program_size(c), 160ul);
  }
  // non-static methods
  void test__program_namespace__1( )
  {
    clxx::program_generator const& g0{ G0{} };
    TS_ASSERT_EQUALS(g0.program_namespace(), "numbo::opencl::programs");
  }
  void test__program_name__1( )
  {
    clxx::program_generator const& g0{ G0{} };
    TS_ASSERT_EQUALS(g0.program_name(), "g0");
  }
  void test__program_full_name__1( )
  {
    clxx::program_generator const& g0{ G0{} };
    TS_ASSERT_EQUALS(g0.program_full_name(), "numbo::opencl::programs::g0");
  }
  void test__program_file_suffix__1( )
  {
    clxx::program_generator const& g0{ G0{} };
    TS_ASSERT_EQUALS(g0.program_file_suffix(), ".cl");
  }
  void test__program_file__1( )
  {
    clxx::program_generator const& g0{ G0{} };
    TS_ASSERT_EQUALS(g0.program_file(), "g0.cl");
  }
  void test__program_dir__1( )
  {
    clxx::program_generator const& g0{ G0{} };
    TS_ASSERT_EQUALS(g0.program_dir(), "numbo/opencl/programs");
  }
  void test__program_path__1( )
  {
    clxx::program_generator const& g0{ G0{} };
    TS_ASSERT_EQUALS(g0.program_path(), "numbo/opencl/programs/g0.cl");
  }
  void test__estimated_program_size__1( )
  {
    program_generator const& g0{ G0{} };
    clxx::context c;
    TS_ASSERT_EQUALS(g0.estimated_program_size(c), 160ul);
  }
  void test__foo( )
  {
    TS_ASSERT(true);
  }
};
/** \endcond */

#endif /* NUMBO_OPENCL_STATIC_PROGRAM_GENERATOR_T_H_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
