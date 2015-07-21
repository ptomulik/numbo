// @COPYRIGHT@
// Licensed under MIT license (LICENSE.txt)

// numbo/opencl/env.t.h

/** // doc: numbo/opencl/env.t.h {{{
 * \file numbo/opencl/env.t.h
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_OPENCL_ENV_T_H_INCLUDED
#define NUMBO_OPENCL_ENV_T_H_INCLUDED

#include <cxxtest/TestSuite.h>
#include <numbo/opencl/env.hpp>

namespace numbo { namespace opencl { class env_test_suite; } }

/** // doc: class numbo::opencl::env_test_suite {{{
 * \todo Write documentation
 */ // }}}
class numbo::opencl::env_test_suite : public CxxTest::TestSuite
{
public:
  /** // doc: test__default_ctor__1() {{{
   * \todo Write documentation
   */ // }}}
  void test__default_ctor__1( )
  {
    TS_ASSERT_EQUALS(env{}.build_options(), "");
  }
  /** // doc: test__build_options__1() {{{
   * \todo Write documentation
   */ // }}}
  void test__build_options__1( )
  {
    TS_ASSERT_THROWS(env().build_options(clxx::context{(cl_context)0x1234}), std::out_of_range);
  }
  /** // doc: test__push_build_options__1() {{{
   * \todo Write documentation
   */ // }}}
  void test__push_build_options__1( )
  {
    clxx::context c{(cl_context)0x1234};
    env e;
    e.push_build_options("-cl-nv-verbose", c);
    TS_ASSERT_EQUALS(e.build_options(c), "-cl_nv_verbose");
    TS_ASSERT_EQUALS(e.build_options(), "");
  }
  /** // doc: test__pop_build_options__1() {{{
   * \todo Write documentation
   */ // }}}
  void test__pop_build_options__1( )
  {
    clxx::context c{(cl_context)0x1234};
    env e;
    e.push_build_options("-cl-nv-verbose", c);
    TS_ASSERT_THROWS_NOTHING(e.pop_build_options(c));
    TS_ASSERT_THROWS(e.pop_build_options(c), std::out_of_range);
    TS_ASSERT_THROWS_NOTHING(e.pop_build_options());
    TS_ASSERT_THROWS(e.pop_build_options(), std::out_of_range);
  }
};

#endif /* NUMBO_OPENCL_ENV_T_H_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
