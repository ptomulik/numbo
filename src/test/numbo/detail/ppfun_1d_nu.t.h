// @COPYRIGHT@
// Licensed under MIT license (LICENSE.txt)

// numbo/detail/ppfun_1d_nu.t.h

/** // doc: numbo/detail/ppfun_1d_nu.t.h {{{
 * \file numbo/detail/ppfun_1d_nu.t.h
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_DETAIL_PPFUN_1D_NU_T_H_INCLUDED
#define NUMBO_DETAIL_PPFUN_1D_NU_T_H_INCLUDED

#include <cxxtest/TestSuite.h>
#include <numbo/detail/ppfun_1d_nu.hpp>

namespace numbo { namespace detail { class Ppfun1dNuTestSuite; } }

/** // doc: class numbo::detail::Ppfun1dNuTestSuite {{{
 * \todo Write documentation
 */ // }}}
class numbo::detail::Ppfun1dNuTestSuite : public CxxTest::TestSuite
{
public:
  /** // doc: test__ppfun_1d_nu_ppform_eval_aux__1() {{{
   * \brief Test ppfun_1d_nu_ppform_eval_aux() for k = 1
   */ // }}}
  void test__ppfun_1d_nu_ppform_eval_aux__1( )
  {
    // f(x) = 2 - a constant function, Df(x) is zero
    const double c[1] = { 2.0 };
    {
      TS_ASSERT_EQUALS(ppfun_1d_nu_ppform_eval_aux(1, 0, c, 1, 0.5), 2.0);
      TS_ASSERT_EQUALS(ppfun_1d_nu_ppform_eval_aux(1, 1, c, 1, 0.5), 0.0);
    }
    
  }
  /** // doc: test__ppfun_1d_nu_ppform_eval_aux__2() {{{
   * \brief Test ppfun_1d_nu_ppform_eval_aux() for k = 2
   */ // }}}
  void test__ppfun_1d_nu_ppform_eval_aux__2( )
  {
    //  f(x)  = 1.0 + 2.0*x;  f(0) = 1.0;
    // Df(x) = 2.0;          Df(0) = 2.0
    const double c[2] = { 1.0, 2.0 };
    {
      // x = 0.5, 
      TS_ASSERT_EQUALS(ppfun_1d_nu_ppform_eval_aux(2, 0, c, 1, 0.5), 2.0);
      TS_ASSERT_EQUALS(ppfun_1d_nu_ppform_eval_aux(2, 1, c, 1, 0.5), 2.0);
      TS_ASSERT_EQUALS(ppfun_1d_nu_ppform_eval_aux(2, 2, c, 1, 0.5), 0.0);
    }

    {
      // x = 1.5, 
      TS_ASSERT_EQUALS(ppfun_1d_nu_ppform_eval_aux(2, 0, c, 1, 1.5), 4.0);
      TS_ASSERT_EQUALS(ppfun_1d_nu_ppform_eval_aux(2, 1, c, 1, 1.5), 2.0);
      TS_ASSERT_EQUALS(ppfun_1d_nu_ppform_eval_aux(2, 2, c, 1, 1.5), 0.0);
    }
  }
  /** // doc: test__ppfun_1d_nu_ppform_eval_aux__3() {{{
   * \brief Test ppfun_1d_nu_ppform_eval_aux() for k = 3
   */ // }}}
  void test__ppfun_1d_nu_ppform_eval_aux__3( )
  {
    //  f(x)  = 1.0 + 2.0*x + 3.0*x^2;   f(0) = 1.0;
    // Df(x)  =       2.0   + 6.0*x;    Df(0) = 2.0
    // D2f(x) =               6.0;     D2f(0) = 6.0
    const double c[3] = { 1.0, 2.0, 6.0 };
    {
      // x = 0.5, 
      TS_ASSERT_EQUALS(ppfun_1d_nu_ppform_eval_aux(3, 0, c, 1, 0.5), 2.75);
      TS_ASSERT_EQUALS(ppfun_1d_nu_ppform_eval_aux(3, 1, c, 1, 0.5), 5.0);
      TS_ASSERT_EQUALS(ppfun_1d_nu_ppform_eval_aux(3, 2, c, 1, 0.5), 6.0);
      TS_ASSERT_EQUALS(ppfun_1d_nu_ppform_eval_aux(3, 3, c, 1, 0.5), 0.0);
    }

    {
      // x = 1.5, 
      TS_ASSERT_EQUALS(ppfun_1d_nu_ppform_eval_aux(3, 0, c, 1, 1.5), 10.75);
      TS_ASSERT_EQUALS(ppfun_1d_nu_ppform_eval_aux(3, 1, c, 1, 1.5), 11.0);
      TS_ASSERT_EQUALS(ppfun_1d_nu_ppform_eval_aux(3, 2, c, 1, 1.5), 6.0);
      TS_ASSERT_EQUALS(ppfun_1d_nu_ppform_eval_aux(3, 3, c, 1, 1.5), 0.0);
    }
  }
  /** // doc: test__ppfun_1d_nu_pprofm_search_gpulike__3() {{{
   * \brief Test ppfun_1d_nu_pprofm_search_gpulike()
   */ // }}}
  void test__ppfun_1d_nu_pprofm_search_gpulike__3( )
  {
    double xi[] = { -INFINITY, 1.00, 2.00, +INFINITY };
    int i;
    int nd;

    nd = 1;
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  -0.01, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  0.00, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  0.99, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  1.00, &i);
    TS_ASSERT_EQUALS(i, 1);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  1.50, &i);
    TS_ASSERT_EQUALS(i, 1);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  2.00, &i);
    TS_ASSERT_EQUALS(i, 2);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  2.50, &i);
    TS_ASSERT_EQUALS(i, 2);

    nd = 2;
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  -0.01, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  0.00, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  0.99, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  1.00, &i);
    TS_ASSERT_EQUALS(i, 1);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  1.50, &i);
    TS_ASSERT_EQUALS(i, 1);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  2.00, &i);
    TS_ASSERT_EQUALS(i, 2);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  2.50, &i);
    TS_ASSERT_EQUALS(i, 2);
    
    nd = 3;
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  -0.01, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  0.00, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  0.99, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  1.00, &i);
    TS_ASSERT_EQUALS(i, 1);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  1.50, &i);
    TS_ASSERT_EQUALS(i, 1);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  2.00, &i);
    TS_ASSERT_EQUALS(i, 2);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  2.50, &i);
    TS_ASSERT_EQUALS(i, 2);

    nd = 4;
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  -0.01, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  0.00, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  0.99, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  1.00, &i);
    TS_ASSERT_EQUALS(i, 1);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  1.50, &i);
    TS_ASSERT_EQUALS(i, 1);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  2.00, &i);
    TS_ASSERT_EQUALS(i, 2);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  2.50, &i);
    TS_ASSERT_EQUALS(i, 2);

    nd = 5;
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  -0.01, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  0.00, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  0.99, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  1.00, &i);
    TS_ASSERT_EQUALS(i, 1);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  1.50, &i);
    TS_ASSERT_EQUALS(i, 1);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  2.00, &i);
    TS_ASSERT_EQUALS(i, 2);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  2.50, &i);
    TS_ASSERT_EQUALS(i, 2);

    nd = 6;
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  -0.01, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  0.00, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  0.99, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  1.00, &i);
    TS_ASSERT_EQUALS(i, 1);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  1.50, &i);
    TS_ASSERT_EQUALS(i, 1);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  2.00, &i);
    TS_ASSERT_EQUALS(i, 2);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  2.50, &i);
    TS_ASSERT_EQUALS(i, 2);

    nd = 3;
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  -0.01, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  0.00, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  0.99, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  1.00, &i);
    TS_ASSERT_EQUALS(i, 1);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  1.50, &i);
    TS_ASSERT_EQUALS(i, 1);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  2.00, &i);
    TS_ASSERT_EQUALS(i, 2);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  2.50, &i);
    TS_ASSERT_EQUALS(i, 2);

    nd = 8;
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  -0.01, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  0.00, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  0.99, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  1.00, &i);
    TS_ASSERT_EQUALS(i, 1);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  1.50, &i);
    TS_ASSERT_EQUALS(i, 1);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  2.00, &i);
    TS_ASSERT_EQUALS(i, 2);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  2.50, &i);
    TS_ASSERT_EQUALS(i, 2);
    
    nd = 9;
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  -0.01, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  0.00, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  0.99, &i);
    TS_ASSERT_EQUALS(i, 0);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  1.00, &i);
    TS_ASSERT_EQUALS(i, 1);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  1.50, &i);
    TS_ASSERT_EQUALS(i, 1);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  2.00, &i);
    TS_ASSERT_EQUALS(i, 2);
    i = -123;
    ppfun_1d_nu_search_interval_gpulike(nd, 3, xi,  2.50, &i);
    TS_ASSERT_EQUALS(i, 2);
  }
  /** // doc: test__ppfun_1d_nu_pprofm_search_linear__3() {{{
   * \brief Test ppfun_1d_nu_pprofm_search_linear()
   */ // }}}
  void test__ppfun_1d_nu_pprofm_search_linear__3( )
  {
    double xi[] = { 0.00, 1.00, 2.00 };
    int i;

    i = ppfun_1d_nu_search_interval_linear(3, xi,  -0.01);
    TS_ASSERT_EQUALS(i, 0);
    i = ppfun_1d_nu_search_interval_linear(3, xi,  0.00);
    TS_ASSERT_EQUALS(i, 0);
    i = ppfun_1d_nu_search_interval_linear(3, xi,  0.99);
    TS_ASSERT_EQUALS(i, 0);
    i = ppfun_1d_nu_search_interval_linear(3, xi,  1.00);
    TS_ASSERT_EQUALS(i, 1);
    i = ppfun_1d_nu_search_interval_linear(3, xi,  1.50);
    TS_ASSERT_EQUALS(i, 1);
    i = ppfun_1d_nu_search_interval_linear(3, xi,  2.00);
    TS_ASSERT_EQUALS(i, 2);
    i = ppfun_1d_nu_search_interval_linear(3, xi,  2.50);
    TS_ASSERT_EQUALS(i, 2);
  }
};

#endif /* NUMBO_DETAIL_PPFUN_1D_NU_T_H_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
