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

namespace Numbo { class UnitTestSuite; }

/** // doc: class Numbo::UnitTestSuite {{{
 * \todo Write documentation
 */ // }}}
class Numbo::UnitTestSuite : public CxxTest::TestSuite
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
