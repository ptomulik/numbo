// @COPYRIGHT@
// Licensed under MIT license (LICENSE.txt)

// numbo/unit.t.h

/** // doc: numbo/unit.t.h {{{
 * \file numbo/unit.t.h
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_DETAIL_ALGO_SEARCH_T_H_INCLUDED
#define NUMBO_DETAIL_ALGO_SEARCH_T_H_INCLUDED

#include <cxxtest/TestSuite.h>
#include <numbo/detail/algo_search.hpp>

namespace numbo { namespace detail { class AlgoSearchTestSuite; } }

/** // doc: class numbo::detail::AlgoSearchTestSuite {{{
 * \todo Write documentation
 */ // }}}
class numbo::detail::AlgoSearchTestSuite : public CxxTest::TestSuite
{
public:
  /** // doc: test__algo_search_linear__01() {{{
   * \todo Write documentation
   */ // }}}
  void test__algo_search_linear__01( )
  {
    float seq[] = { 0.0, 1.0, 2.0, 3.0, 4.0 };
    const int n = 5;
    int pos;

    algo_search_linear(n, seq, -0.1, &pos);
    TS_ASSERT_EQUALS(pos, -1);

    algo_search_linear(n, seq, 0.0, &pos);
    TS_ASSERT_EQUALS(pos, 0);

    algo_search_linear(n, seq, 0.2, &pos);
    TS_ASSERT_EQUALS(pos, 0);

    algo_search_linear(n, seq, 1.0, &pos);
    TS_ASSERT_EQUALS(pos, 1);

    algo_search_linear(n, seq, 1.2, &pos);
    TS_ASSERT_EQUALS(pos, 1);

    algo_search_linear(n, seq, 2.2, &pos);
    TS_ASSERT_EQUALS(pos, 2);

    algo_search_linear(n, seq, 3.3, &pos);
    TS_ASSERT_EQUALS(pos, 3);

    algo_search_linear(n, seq, 4.0, &pos);
    TS_ASSERT_EQUALS(pos, 4);
  }
};

#endif /* NUMBO_DETAIL_ALGO_SEARCH_T_H_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
