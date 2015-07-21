// @COPYRIGHT@
// Licensed under MIT license (LICENSE.txt)

// numbo/unit.t.h

/** // doc: numbo/unit.t.h {{{
 * \file numbo/unit.t.h
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_UNIT_T_H_INCLUDED
#define NUMBO_UNIT_T_H_INCLUDED

#include <cxxtest/TestSuite.h>
#include <numbo/unit.hpp>

namespace numbo { class unit_test_suite; }

/** // doc: class numbo::unit_test_suite {{{
 * \todo Write documentation
 */ // }}}
class numbo::unit_test_suite : public CxxTest::TestSuite
{
public:
  /** // doc: test__foo() {{{
   * \todo Write documentation
   */ // }}}
  void test__foo( )
  {
    TS_ASSERT(true);
  }
};

#endif /* NUMBO_UNIT_T_H_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
