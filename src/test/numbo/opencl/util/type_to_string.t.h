// @COPYRIGHT@
// Licensed under MIT license (LICENSE.txt)

// numbo/opencl/util/type_to_string.t.h

/** // doc: numbo/opencl/util/type_to_string.t.h {{{
 * \file numbo/opencl/util/type_to_string.t.h
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_OPENCL_UTIL_TYPE_TO_STRING_T_H_INCLUDED
#define NUMBO_OPENCL_UTIL_TYPE_TO_STRING_T_H_INCLUDED

#include <cxxtest/TestSuite.h>
#include <numbo/opencl/util/type_to_string.hpp>

namespace numbo { namespace opencl { namespace util { class TypeToStringTestSuite; } } }

/** // doc: class numbo::opencl::util::TypeToStringTestSuite {{{
 * \todo Write documentation
 */ // }}}
class numbo::opencl::util::TypeToStringTestSuite : public CxxTest::TestSuite
{
public:
  /** // doc: test__type_to_string__char() {{{
   * \todo Write documentation
   */ // }}}
  void test__type_to_string__char( )
  {
    TS_ASSERT_EQUALS(type_to_string<cl_char>::apply(), "char");
  }
  /** // doc: test__type_to_string__short() {{{
   * \todo Write documentation
   */ // }}}
  void test__type_to_string__short( )
  {
    TS_ASSERT_EQUALS(type_to_string<cl_short>::apply(), "short");
  }
  /** // doc: test__type_to_string__int() {{{
   * \todo Write documentation
   */ // }}}
  void test__type_to_string__int( )
  {
    TS_ASSERT_EQUALS(type_to_string<cl_int>::apply(), "int");
  }
  /** // doc: test__type_to_string__long() {{{
   * \todo Write documentation
   */ // }}}
  void test__type_to_string__long( )
  {
    TS_ASSERT_EQUALS(type_to_string<cl_long>::apply(), "long");
  }
  /** // doc: test__type_to_string__uchar() {{{
   * \todo Write documentation
   */ // }}}
  void test__type_to_string__uchar( )
  {
    TS_ASSERT_EQUALS(type_to_string<cl_uchar>::apply(), "uchar");
  }
  /** // doc: test__type_to_string__ushort() {{{
   * \todo Write documentation
   */ // }}}
  void test__type_to_string__ushort( )
  {
    TS_ASSERT_EQUALS(type_to_string<cl_ushort>::apply(), "ushort");
  }
  /** // doc: test__type_to_string__uint() {{{
   * \todo Write documentation
   */ // }}}
  void test__type_to_string__uint( )
  {
    TS_ASSERT_EQUALS(type_to_string<cl_uint>::apply(), "uint");
  }
  /** // doc: test__type_to_string__ulong() {{{
   * \todo Write documentation
   */ // }}}
  void test__type_to_string__ulong( )
  {
    TS_ASSERT_EQUALS(type_to_string<cl_ulong>::apply(), "ulong");
  }
  /** // doc: test__type_to_string__float() {{{
   * \todo Write documentation
   */ // }}}
  void test__type_to_string__float( )
  {
    TS_ASSERT_EQUALS(type_to_string<cl_float>::apply(), "float");
  }
  /** // doc: test__type_to_string__double() {{{
   * \todo Write documentation
   */ // }}}
  void test__type_to_string__double( )
  {
    TS_ASSERT_EQUALS(type_to_string<cl_double>::apply(), "double");
  }
  /** // doc: test__type_to_string__half() {{{
   * \todo Write documentation
   */ // }}}
  void test__type_to_string__half( )
  {
    TS_ASSERT_EQUALS((type_to_string<cl_half, floating_type_tag>::apply()), "half");
  }
};

#endif /* NUMBO_OPENCL_UTIL_TYPE_TO_STRING_T_H_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
