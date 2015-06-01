// @COPYRIGHT@
// Licensed under MIT license (LICENSE.txt)

// numbo/detail/bspline_1d_nu.t.h

/** // doc: numbo/detail/bspline_1d_nu.t.h {{{
 * \file numbo/detail/bspline_1d_nu.t.h
 * \brief Unit tests for numbo/detail/bspline_1d_nu.hpp
 */ // }}}
#ifndef NUMBO_DETAIL_BSPLINE_1D_NU_T_H_INCLUDED
#define NUMBO_DETAIL_BSPLINE_1D_NU_T_H_INCLUDED

#include <cxxtest/TestSuite.h>
#include <numbo/detail/bspline_1d_nu.hpp>
#include <limits>
#include <cmath>

namespace Numbo { namespace Detail { class Bspline1dNuTestSuite; } }

/** // doc: class Numbo::Bspline1dNuTestSuite {{{
 * \todo Write documentation
 */ // }}}
class Numbo::Detail::Bspline1dNuTestSuite : public CxxTest::TestSuite
{
protected:
  static bool same(double a, double b)
  {
    return std::fabs(a - b) < std::numeric_limits<double>::epsilon();
  }
public:
  /** // doc: test__bspline_1d_nu_deltas__0() {{{
   * \brief Test bspline_1d_nu_deltas() for k = 0
   *
   * Not tested. Note, we require k > 0.
   */ // }}}
//  void test__bspline_1d_nu_deltas__0( )
//  {
//    // With k=0 the function shouldn't dereference any pointers. The provided
//    // values of i and x should also be non-important. The function shouldn't
//    // crash, nor throw anything.
//    double const * const ti = nullptr;
//    double * const dk = nullptr;
//    TS_ASSERT_THROWS_NOTHING(bspline_1d_nu_deltas(0, ti, 0.0, dk));
//  }
  /** // doc: test__bspline_1d_nu_deltas__1() {{{
   * \brief Test bspline_1d_nu_deltas() for k = 1
   */ // }}}
  void test__bspline_1d_nu_deltas__1( )
  {
    // With k=1 the function shouldn't dereference any pointers. The provided
    // values of i and x should also be non-important. The function shouldn't
    // crash, nor throw anything.
    double const * const ti = nullptr;
    double * const dk = nullptr;
    TS_ASSERT_THROWS_NOTHING(bspline_1d_nu_deltas(1, ti, 0.0, dk));
  }
  /** // doc: test__bspline_1d_nu_deltas__2() {{{
   * \brief Test bspline_1d_nu_deltas() for k = 2
   */ // }}}
  void test__bspline_1d_nu_deltas__2( )
  {
    // With k=2 the function should compute dk[0] and dk[1].
    double const t[] = {0.0, 1.0, 2.0, 3.0};
    double dk[2] = {-1.234, -1.234};
    TS_ASSERT_THROWS_NOTHING(bspline_1d_nu_deltas(2, t+1, 1.3, dk));
    TS_ASSERT_EQUALS(dk[0], (1.3 - 1.0));
    TS_ASSERT_EQUALS(dk[1], (1.3 - 2.0));
  }
  /** // doc: test__bspline_1d_nu_deltas__3() {{{
   * \brief Test bspline_1d_nu_deltas() for k = 3
   */ // }}}
  void test__bspline_1d_nu_deltas__3( )
  {
    // With k=3 the function should compute dk[0] .. d[3].
    double const t[] = {0.0, 1.0, 2.0, 3.0};
    double dk[4] = {-1.234, -1.234, -1.234, -1.234};
    TS_ASSERT_THROWS_NOTHING(bspline_1d_nu_deltas(3, t+1, 1.3, dk));
    TS_ASSERT_EQUALS(dk[0], (1.3 - 0.0));
    TS_ASSERT_EQUALS(dk[1], (1.3 - 1.0));
    TS_ASSERT_EQUALS(dk[2], (1.3 - 2.0));
    TS_ASSERT_EQUALS(dk[3], (1.3 - 3.0));
  }
  /** // doc: test__bspline_1d_nu_deltas__4() {{{
   * \brief Test bspline_1d_nu_deltas() for k = 4
   */ // }}}
  void test__bspline_1d_nu_deltas__4( )
  {
    // With k=4 the function should compute dk[0] .. d[5].
    double const t[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
    double dk[6] = {-1.234, -1.234, -1.234, -1.234, -1.234, -1.234};
    TS_ASSERT_THROWS_NOTHING(bspline_1d_nu_deltas(4, t+2, 2.3, dk));
    TS_ASSERT_EQUALS(dk[0], (2.3 - 0.0));
    TS_ASSERT_EQUALS(dk[1], (2.3 - 1.0));
    TS_ASSERT_EQUALS(dk[2], (2.3 - 2.0));
    TS_ASSERT_EQUALS(dk[3], (2.3 - 3.0));
    TS_ASSERT_EQUALS(dk[4], (2.3 - 4.0));
    TS_ASSERT_EQUALS(dk[5], (2.3 - 5.0));
  }
//  /** // doc: test__bspline_1d_nu_bvalues__0() {{{
//   * \brief Test bspline_1d_nu_bvalues() for ko = 0
//   */ // }}}
//  void test__bspline_1d_nu_bvalues__0( )
//  {
//    // With ko=0 the function shouldn't dereference any pointers.
//    // The function shouldn't crash, nor throw anything.
//    double const* dkl = nullptr;
//    double const* dkr = nullptr;
//    double* b = nullptr;
//    TS_ASSERT_THROWS_NOTHING(bspline_1d_nu_bvalues(5, dkl, dkr, 0, 0, b));
//  }
  /** // doc: test__bspline_1d_nu_bvalues__1() {{{
   * \brief Test bspline_1d_nu_bvalues() for ko = 1
   */ // }}}
  void test__bspline_1d_nu_bvalues__1( )
  {
    // With ko=1 the function shouldn't dereference dkl and dkr. 
    // The function shouldn't crash, nor throw anything.
    double const* dk = nullptr;
    double b[1] = {-1.234};
    TS_ASSERT_THROWS_NOTHING(bspline_1d_nu_bvalues(5, dk, 0, 1, b));
    TS_ASSERT_EQUALS(b[0], 1.0);
  }
  /** // doc: test__bspline_1d_nu_bvalues__2() {{{
   * \brief Test bspline_1d_nu_bvalues() for ko = 2
   */ // }}}
  void test__bspline_1d_nu_bvalues__2( )
  {
    double const dk[] = {(1.3 - 1.0), (1.3 - 2.0)};
    double b[2] = {-1.234, -1.234};
    TS_ASSERT_THROWS_NOTHING(bspline_1d_nu_bvalues(2, dk, 0, 2, b));
    TS_ASSERT(same(b[0], 0.7));
    TS_ASSERT(same(b[1], 0.3));
  }
  /** // doc: test__bspline_1d_nu_bvalues__3__0() {{{
   * \brief Test bspline_1d_nu_bvalues() for ko = 3
   */ // }}}
  void test__bspline_1d_nu_bvalues__3__0( )
  {
    double const dk[] = {(1.3 - 0.0), (1.3 - 1.0), (1.3 - 2.0), (1.3 - 3.0)};
    double b[3] = {-1.234, -1.234, -1.234};
    TS_ASSERT_THROWS_NOTHING(bspline_1d_nu_bvalues(3, dk, 0, 3, b));
    TS_ASSERT(same(b[0], 0.245));
    TS_ASSERT(same(b[1], 0.710));
    TS_ASSERT(same(b[2], 0.045));
  }
  /** // doc: test__bspline_1d_nu_bvalues__3__1() {{{
   * \brief Test bspline_1d_nu_bvalues() for ki=1, ko = 3
   */ // }}}
  void test__bspline_1d_nu_bvalues__3__1( )
  {
    double const dk[] = {(1.3 - 0.0), (1.3 - 1.0), (1.3 - 2.0), (1.3 - 3.0)};
    double b[3] = {1, -1.234, -1.234};
    TS_ASSERT_THROWS_NOTHING(bspline_1d_nu_bvalues(3, dk, 1, 3, b));
    TS_ASSERT(same(b[0], 0.245));
    TS_ASSERT(same(b[1], 0.710));
    TS_ASSERT(same(b[2], 0.045));
  }
  /** // doc: test__bspline_1d_nu_bvalues__3__2() {{{
   * \brief Test bspline_1d_nu_bvalues() for ki=2, ko = 3
   */ // }}}
  void test__bspline_1d_nu_bvalues__3__2( )
  {
    double const dk[] = {(1.3 - 0.0), (1.3 - 1.0), (1.3 - 2.0), (1.3 - 3.0)};
    double b[3] = {0.7, 0.3, -1.234};
    TS_ASSERT_THROWS_NOTHING(bspline_1d_nu_bvalues(3, dk, 2, 3, b));
    TS_ASSERT(same(b[0], 0.245));
    TS_ASSERT(same(b[1], 0.710));
    TS_ASSERT(same(b[2], 0.045));
  }
  /** // doc: test__bspline_1d_nu_bvalues_w_stride__1() {{{
   * \brief Test bspline_1d_nu_bvalues_w_stride() for ko = 1
   */ // }}}
  void test__bspline_1d_nu_bvalues_w_stride__1( )
  {
    // With ko=1 the function shouldn't dereference dkl and dkr. 
    // The function shouldn't crash, nor throw anything.
    double const* dk = nullptr;
    double b[1] = {-1.234};
    TS_ASSERT_THROWS_NOTHING(bspline_1d_nu_bvalues_w_stride(5, dk, 0, 1, 3, b));
    TS_ASSERT_EQUALS(b[0], 1.0);
  }
  /** // doc: test__bspline_1d_nu_bvalues_w_stride__2() {{{
   * \brief Test bspline_1d_nu_bvalues_w_stride() for ko = 2
   */ // }}}
  void test__bspline_1d_nu_bvalues_w_stride__2( )
  {
    double const dk[] = {(1.3 - 1.0), (1.3 - 2.0)};
    double b[6] = {-1.234, -1.234, -1.234, -1.234, -1.234, -1.234};
    TS_ASSERT_THROWS_NOTHING(bspline_1d_nu_bvalues_w_stride(2, dk, 0, 2, 3, b));
    TS_ASSERT(same(b[0], 0.7));
    TS_ASSERT(same(b[1], -1.234));
    TS_ASSERT(same(b[2], -1.234));
    TS_ASSERT(same(b[3], 0.3));
    TS_ASSERT(same(b[4], -1.234));
    TS_ASSERT(same(b[5], -1.234));
  }
  /** // doc: test__bspline_1d_nu_bvalues_w_stride__3__0() {{{
   * \brief Test bspline_1d_nu_bvalues_w_stride() for ko = 3
   */ // }}}
  void test__bspline_1d_nu_bvalues_w_stride__3__0( )
  {
    double const dk[] = {(1.3 - 0.0), (1.3 - 1.0), (1.3 - 2.0), (1.3 - 3.0)};
    double b[9] = {-1.234, -1.234, -1.234, -1.234, -1.234, -1.234, -1.234, -1.234, -1.234};
    TS_ASSERT_THROWS_NOTHING(bspline_1d_nu_bvalues_w_stride(3, dk, 0, 3, 3, b));
    TS_ASSERT(same(b[0], 0.245));
    TS_ASSERT(same(b[1], -1.234));
    TS_ASSERT(same(b[2], -1.234));
    TS_ASSERT(same(b[3], 0.710));
    TS_ASSERT(same(b[4], -1.234));
    TS_ASSERT(same(b[5], -1.234));
    TS_ASSERT(same(b[6], 0.045));
    TS_ASSERT(same(b[7], -1.234));
    TS_ASSERT(same(b[8], -1.234));
  }
  /** // doc: test__bspline_1d_nu_bvalues_w_stride__3__1() {{{
   * \brief Test bspline_1d_nu_bvalues_w_stride() for ki=1, ko = 3
   */ // }}}
  void test__bspline_1d_nu_bvalues_w_stride__3__1( )
  {
    double const dk[] = {(1.3 - 0.0), (1.3 - 1.0), (1.3 - 2.0), (1.3 - 3.0)};
    double b[9] = {1, -1.234, -1.234, -1.234, -1.234, -1.234, -1.234, -1.234, -1.234};
    TS_ASSERT_THROWS_NOTHING(bspline_1d_nu_bvalues_w_stride(3, dk, 1, 3, 3, b));
    TS_ASSERT(same(b[0], 0.245));
    TS_ASSERT(same(b[1], -1.234));
    TS_ASSERT(same(b[1], -1.234));
    TS_ASSERT(same(b[3], 0.710));
    TS_ASSERT(same(b[4], -1.234));
    TS_ASSERT(same(b[5], -1.234));
    TS_ASSERT(same(b[6], 0.045));
    TS_ASSERT(same(b[7], -1.234));
    TS_ASSERT(same(b[8], -1.234));
  }
  /** // doc: test__bspline_1d_nu_bvalues_w_stride__3__2() {{{
   * \brief Test bspline_1d_nu_bvalues_w_stride() for ki=2, ko = 3
   */ // }}}
  void test__bspline_1d_nu_bvalues_w_stride__3__2( )
  {
    double const dk[] = {(1.3 - 0.0), (1.3 - 1.0), (1.3 - 2.0), (1.3 - 3.0)};
    double b[9] = {0.7, -1.234, -1.234, 0.3, -1.234, -1.234, -1.234, -1.234, -1.234};
    TS_ASSERT_THROWS_NOTHING(bspline_1d_nu_bvalues_w_stride(3, dk, 2, 3, 3, b));
    TS_ASSERT(same(b[0], 0.245));
    TS_ASSERT(same(b[1], -1.234));
    TS_ASSERT(same(b[1], -1.234));
    TS_ASSERT(same(b[3], 0.710));
    TS_ASSERT(same(b[4], -1.234));
    TS_ASSERT(same(b[5], -1.234));
    TS_ASSERT(same(b[6], 0.045));
    TS_ASSERT(same(b[7], -1.234));
    TS_ASSERT(same(b[8], -1.234));
  }
  /** // doc: test__bspline_1d_nu_interp_spcol__1() {{{
   * \brief Test bspline_1d_nu_interp_spcol() for k=1
   */ // }}}
  void test__bspline_1d_nu_interp_spcol__1( )
  {
    const size_t k    = 1;
    const size_t mb   = 1 + 2*(k-1);
    {
      // site at the left end of basic interval
      const size_t n      = 1;
      const double t[n+k] = {0.0, 1.0};
      const double x[n]   = {0.0};
      double b[mb * n]    = {0.0};

      size_t r = bspline_1d_nu_interp_spcol(k, n, t, x, 0, (double*)nullptr, mb, b);
      TS_ASSERT_EQUALS(r, n);
      TS_ASSERT_EQUALS(b[0], 1.0);
    }
    {
      // site at the right end of basic interval
      const size_t n      = 1;
      const double t[n+k] = {0.0, 1.0};
      const double x[n]   = {1.0};
      double b[mb * n]    = {0.0};

      size_t r = bspline_1d_nu_interp_spcol(k, n, t, x, 0, (double*)nullptr, mb, b);
      TS_ASSERT_EQUALS(r, n);
      TS_ASSERT_EQUALS(b[0], 1.0);
    }
    {
      // site in the middle of basic interval
      const size_t n      = 1;
      const double t[n+k] = {0.0, 1.0};
      const double x[n]   = {0.5};
      double b[mb * n]    = {0.0};

      size_t r = bspline_1d_nu_interp_spcol(k, n, t, x, 0, (double*)nullptr, mb, b);
      TS_ASSERT_EQUALS(r, n);
      TS_ASSERT_EQUALS(b[0], 1.0);
    }
    {
      // two sites in the middle of basic interval
      const size_t n      = 2;
      const double t[n+k] = {0.0, 0.5, 1.0};
      const double x[n]   = {0.3, 0.7};
      double b[mb * n]    = {0.0};

      size_t r = bspline_1d_nu_interp_spcol(k, n, t, x, 0, (double*)nullptr, mb, b);
      TS_ASSERT_EQUALS(r, n);
      TS_ASSERT_EQUALS(b[0], 1.0);
      TS_ASSERT_EQUALS(b[1], 1.0);
    }
    {
      // two sites at knots and one in the middle
      const size_t n      = 3;
      const double t[n+k] = {0.0, 0.3,     0.6, 1.0};
      const double x[n]   = {0.0,     0.5,      1.0};
      double b[mb * n]    = {0.0};

      size_t r = bspline_1d_nu_interp_spcol(k, n, t, x, 0, (double*)nullptr, mb, b);
      TS_ASSERT_EQUALS(r, n);
      TS_ASSERT_EQUALS(b[0], 1.0);
      TS_ASSERT_EQUALS(b[1], 1.0);
      TS_ASSERT_EQUALS(b[2], 1.0);
    }
    {
      // all sites at the knots, but remember: k=1, so all knots have its
      // maximum possible multiplicity
      const size_t n      = 3;
      const double t[n+k] = {0.0, 0.3, 0.6, 1.0};
      const double x[n]   = {0.0, 0.3, 0.6};
      double b[mb * n]    = {0.0};

      size_t r = bspline_1d_nu_interp_spcol(k, n, t, x, 0, (double*)nullptr, mb, b);
      TS_ASSERT_EQUALS(r, n);
      TS_ASSERT_EQUALS(b[0], 1.0);
      TS_ASSERT_EQUALS(b[1], 1.0);
      TS_ASSERT_EQUALS(b[2], 1.0);
    }
    {
      // site outside of basic interval (at left)
      const size_t n      = 1;
      const double t[n+k] = {0.0, 1.0};
      const double x[n]   = {-1.0};
      double b[mb * n]    = {0.0};

      size_t r = bspline_1d_nu_interp_spcol(k, n, t, x, 0, (double*)nullptr, mb, b);
      TS_ASSERT_EQUALS(r, 0);
      TS_ASSERT_EQUALS(b[0], 0.0);
    }
    {
      // site outside of basic interval (at right)
      const size_t n      = 1;
      const double t[n+k] = {0.0, 1.0};
      const double x[n]   = {2.0};
      double b[mb * n]    = {0.0};

      size_t r = bspline_1d_nu_interp_spcol(k, n, t, x, 0, (double*)nullptr, mb, b);
      TS_ASSERT_EQUALS(r, 0);
      TS_ASSERT_EQUALS(b[0], 0.0);
    }
  }
  /** // doc: test__bspline_1d_nu_interp_spcol__2() {{{
   * \brief Test bspline_1d_nu_interp_spcol() for k=2
   */ // }}}
  void test__bspline_1d_nu_interp_spcol__2( )
  {
    const size_t k = 2;
    const size_t md = 2*(k-1);
    const size_t mb = 1 + 2*(k-1);
    {
      // n < k, thus matrix is not invertible
      const size_t  n = 1;
      const double  t[n+k]  = { 0.0, 0.0, 1.0 };
      const double  x[n]    = { 0.0 };
      double        d[md*n];
      double        b[mb*n] = {0.0};
      size_t r = bspline_1d_nu_interp_spcol(k, n, t, x, md, d, mb, b);
      TS_ASSERT_EQUALS(r, 0);
      TS_ASSERT_EQUALS(b[0], 0.0);
      TS_ASSERT_EQUALS(b[1], 0.0);
      TS_ASSERT_EQUALS(b[2], 0.0);
    }
    {
      // n < k, thus matrix is not invertible
      const size_t  n = 1;
      const double  t[n+k]  = { 0.0, 0.0, 1.0 };
      const double  x[n]    = { 1.0 };
      double        d[md*n];
      double        b[mb*n] = {0.0};
      size_t r = bspline_1d_nu_interp_spcol(k, n, t, x, md, d, mb, b);
      TS_ASSERT_EQUALS(r, 0);
      TS_ASSERT_EQUALS(b[0], 0.0);
      TS_ASSERT_EQUALS(b[1], 0.0);
      TS_ASSERT_EQUALS(b[2], 0.0);
    }
    {
      // sites at the left and right knot
      const size_t  n = 2;
      const double  t[n+k]  = { 0.0, 0.0, 1.0, 1.0 };
      const double  x[n]    = {      0.0, 1.0 };
      double        d[md*n];
      double        b[mb*n] = {0.0};
      size_t r = bspline_1d_nu_interp_spcol(k, n, t, x, md, d, mb, b);
      TS_ASSERT_EQUALS(r, n);
      TS_ASSERT_EQUALS(b[0], 0.0);
      TS_ASSERT(same(b[1], 1.0));
      TS_ASSERT(same(b[2], 0.0));
      TS_ASSERT(same(b[3], 0.0));
      TS_ASSERT(same(b[4], 1.0));
      TS_ASSERT_EQUALS(b[5], 0.0);
    }
    {
      // sites at the left and in the middle
      const size_t  n = 2;
      const double  t[n+k]  = { 0.0, 0.0,      1.0, 1.0 };
      const double  x[n]    = {      0.0, 0.3 };
      double        d[md*n];
      double        b[mb*n] = {0.0};
      size_t r = bspline_1d_nu_interp_spcol(k, n, t, x, md, d, mb, b);
      TS_ASSERT_EQUALS(r, n);
      TS_ASSERT_EQUALS(b[0], 0.0);
      TS_ASSERT(same(b[1], 1.0));
      TS_ASSERT(same(b[2], 0.7));
      TS_ASSERT(same(b[3], 0.0));
      TS_ASSERT(same(b[4], 0.3));
      TS_ASSERT_EQUALS(b[5], 0.0);
    }
    {
      // sites in the middle and at the right
      const size_t  n = 2;
      const double  t[n+k]  = { 0.0, 0.0,      1.0, 1.0 };
      const double  x[n]    = {           0.3, 1.0 };
      double        d[md*n];
      double        b[mb*n] = {0.0};
      size_t r = bspline_1d_nu_interp_spcol(k, n, t, x, md, d, mb, b);
      TS_ASSERT_EQUALS(r, n);
      TS_ASSERT_EQUALS(b[0], 0.0);
      TS_ASSERT(same(b[1], 0.7));
      TS_ASSERT(same(b[2], 0.0));
      TS_ASSERT(same(b[3], 0.3));
      TS_ASSERT(same(b[4], 1.0));
      TS_ASSERT_EQUALS(b[5], 0.0);
    }
    {
      // sites in the middle
      const size_t  n = 2;
      const double  t[n+k]  = { 0.0, 0.0,          1.0, 1.0 };
      const double  x[n]    = {           0.3, 0.7 };
      double        d[md*n];
      double        b[mb*n] = {0.0};
      size_t r = bspline_1d_nu_interp_spcol(k, n, t, x, md, d, mb, b);
      TS_ASSERT_EQUALS(r, n);
      TS_ASSERT_EQUALS(b[0], 0.0);
      TS_ASSERT(same(b[1], 0.7));
      TS_ASSERT(same(b[2], 0.3));
      TS_ASSERT(same(b[3], 0.3));
      TS_ASSERT(same(b[4], 0.7));
      TS_ASSERT_EQUALS(b[5], 0.0);
    }
  }
  /** // doc: test__bspline_1d_nu_interp_spcol__3() {{{
   * \brief Test bspline_1d_nu_interp_spcol() for k=2
   */ // }}}
  void test__bspline_1d_nu_interp_spcol__3( )
  {
    const size_t k = 3;
    const size_t md = 2*(k-1);
    const size_t mb = 1 + 2*(k-1);
    {
      // n < k, thus matrix can't be invertible
      const size_t  n = 1;
      const double  t[n+k]  = { 0.0, 0.0, 0.0, 1.0 };
      const double  x[n]    = { 0.0 };
      double        d[md*n];
      double        b[mb*n] = {0.0};
      size_t r = bspline_1d_nu_interp_spcol(k, n, t, x, md, d, mb, b);
      TS_ASSERT_EQUALS(r, 0);
      TS_ASSERT_EQUALS(b[0], 0.0);
      TS_ASSERT_EQUALS(b[1], 0.0);
      TS_ASSERT_EQUALS(b[2], 0.0);
      TS_ASSERT_EQUALS(b[3], 0.0);
      TS_ASSERT_EQUALS(b[4], 0.0);
    }
    {
      // n < k, thus matrix can't be invertible
      const size_t  n = 1;
      const double  t[n+k]  = { 0.0, 0.0, 0.0, 1.0 };
      const double  x[n]    = { 1.0 };
      double        d[md*n];
      double        b[mb*n] = {0.0};
      size_t r = bspline_1d_nu_interp_spcol(k, n, t, x, md, d, mb, b);
      TS_ASSERT_EQUALS(r, 0);
      TS_ASSERT_EQUALS(b[0], 0.0);
      TS_ASSERT_EQUALS(b[1], 0.0);
      TS_ASSERT_EQUALS(b[2], 0.0);
      TS_ASSERT_EQUALS(b[3], 0.0);
      TS_ASSERT_EQUALS(b[4], 0.0);
    }
    {
      // n < k, thus matrix can't be invertible
      const size_t  n = 1;
      const double  t[n+k]  = { 0.0, 0.0, 0.0, 1.0 };
      const double  x[n]    = { 0.5 };
      double        d[md*n];
      double        b[mb*n] = {0.0};
      size_t r = bspline_1d_nu_interp_spcol(k, n, t, x, md, d, mb, b);
      TS_ASSERT_EQUALS(r, 0);
      TS_ASSERT_EQUALS(b[0], 0.0);
      TS_ASSERT_EQUALS(b[1], 0.0);
      TS_ASSERT_EQUALS(b[2], 0.0);
      TS_ASSERT_EQUALS(b[3], 0.0);
      TS_ASSERT_EQUALS(b[4], 0.0);
    }
    {
      // n < k, thus matrix can't be invertible
      const size_t  n = 2;
      const double  t[n+k]  = { 0.0, 0.0, 0.0, 1.0, 1.0 };
      const double  x[n]    = { 0.0, 1.0 };
      double        d[md*n];
      double        b[mb*n] = {0.0};
      size_t r = bspline_1d_nu_interp_spcol(k, n, t, x, md, d, mb, b);
      TS_ASSERT_EQUALS(r, 0);
      TS_ASSERT_EQUALS(b[0], 0.0);
      TS_ASSERT_EQUALS(b[1], 0.0);
      TS_ASSERT_EQUALS(b[2], 0.0);
      TS_ASSERT_EQUALS(b[3], 0.0);
      TS_ASSERT_EQUALS(b[4], 0.0);
      TS_ASSERT_EQUALS(b[5], 0.0);
      TS_ASSERT_EQUALS(b[6], 0.0);
      TS_ASSERT_EQUALS(b[7], 0.0);
      TS_ASSERT_EQUALS(b[8], 0.0);
      TS_ASSERT_EQUALS(b[9], 0.0);
    }
    {
      // two sites at knots and one site in the middle
      const size_t  n = 3;
      const double  t[n+k]  = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0 };
      const double  x[n]    = { 0.0, 0.3, 1.0 };
      double        d[md*n];
      double        b[mb*n] = {0.0};
      size_t r = bspline_1d_nu_interp_spcol(k, n, t, x, md, d, mb, b);
      TS_ASSERT_EQUALS(r, n);

      // Numbers taken from Matlab's call: spcol(t, 3, [0, 0.3, 0.1])
      TS_ASSERT_EQUALS(b[0], 0.0);
      TS_ASSERT_EQUALS(b[1], 0.0);
      TS_ASSERT(same(b[2], 1.00));
      TS_ASSERT(same(b[3], 0.49));
      TS_ASSERT(same(b[4], 0.00));

      TS_ASSERT_EQUALS(b[5], 0.0);
      TS_ASSERT(same(b[6], 0.00));
      TS_ASSERT(same(b[7], 0.42));
      TS_ASSERT(same(b[8], 0.00));
      TS_ASSERT_EQUALS(b[9], 0.0);

      TS_ASSERT(same(b[10], 0.00));
      TS_ASSERT(same(b[11], 0.09))
      TS_ASSERT(same(b[12], 1.00));
      TS_ASSERT_EQUALS(b[13], 0.0);
      TS_ASSERT_EQUALS(b[14], 0.0);
    }
    {
      // three sites at knots and two sites in between
      const size_t  n = 5;
      const double  t[n+k]  = { 0.0, 0.0, 0.0,      0.5, 0.5,      1.0, 1.0, 1.0 };
      const double  x[n]    = {           0.0, 0.3,    0.5,   0.7, 1.0 };
      double        d[md*n];
      double        b[mb*n] = {0.0};
      size_t r = bspline_1d_nu_interp_spcol(k, n, t, x, md, d, mb, b);
      TS_ASSERT_EQUALS(r, n);

      // Numbers taken from Matlab's call: spcol(t, 3, [0, 0.3, 0.5, 0.7, 0.1])
      TS_ASSERT_EQUALS(b[0], 0.0);
      TS_ASSERT_EQUALS(b[1], 0.0);
      TS_ASSERT(same(b[2], 1.00));
      TS_ASSERT(same(b[3], 0.16));
      TS_ASSERT(same(b[4], 0.00));

      TS_ASSERT_EQUALS(b[5], 0.0);
      TS_ASSERT(same(b[6], 0.00));
      TS_ASSERT(same(b[7], 0.48));
      TS_ASSERT(same(b[8], 0.00));
      TS_ASSERT(same(b[9], 0.00));

      TS_ASSERT(same(b[10], 0.00));
      TS_ASSERT(same(b[11], 0.36))
      TS_ASSERT(same(b[12], 1.00));
      TS_ASSERT(same(b[13], 0.36));
      TS_ASSERT(same(b[14], 0.00));

      TS_ASSERT(same(b[15], 0.00));
      TS_ASSERT(same(b[16], 0.00))
      TS_ASSERT(same(b[17], 0.48));
      TS_ASSERT(same(b[18], 0.00));
      TS_ASSERT_EQUALS(b[19], 0.0);

      TS_ASSERT(same(b[20], 0.00));
      TS_ASSERT(same(b[21], 0.16))
      TS_ASSERT(same(b[22], 1.00));
      TS_ASSERT_EQUALS(b[23], 0.0);
      TS_ASSERT_EQUALS(b[24], 0.0);
    }
    {
      // a case which would yield a singular collocation matrix
      const size_t  n = 6;
      const double  t[n+k]  = { 0.0, 0.0, 0.0,       0.5, 0.5, 0.5,           1.0, 1.0, 1.0 };
      const double  x[n]    = {           0.0, 0.3,       0.5,      0.6, 0.7, 1.0 };
      double        d[md*n];
      double        b[mb*n] = {0.0};
      size_t r = bspline_1d_nu_interp_spcol(k, n, t, x, md, d, mb, b);
      TS_ASSERT_EQUALS(r, n);

      // Numbers taken from Matlab's call: spcol(t, 3, [0, 0.3, 0.5, 0.7, 0.1])
      TS_ASSERT_EQUALS(b[0], 0.0);
      TS_ASSERT_EQUALS(b[1], 0.0);
      TS_ASSERT(same(b[2], 1.00));
      TS_ASSERT(same(b[3], 0.16));
      TS_ASSERT(same(b[4], 0.00));

      TS_ASSERT_EQUALS(b[5], 0.0);
      TS_ASSERT(same(b[6], 0.00));
      TS_ASSERT(same(b[7], 0.48));
      TS_ASSERT(same(b[8], 0.00));
      TS_ASSERT(same(b[9], 0.00));

      TS_ASSERT(same(b[10], 0.00));
      TS_ASSERT(same(b[11], 0.36))
      TS_ASSERT(same(b[12], 0.00));
      TS_ASSERT(same(b[13], 0.00));
      TS_ASSERT(same(b[14], 0.00));

      TS_ASSERT(same(b[15], 0.00));
      TS_ASSERT(same(b[16], 1.00))
      TS_ASSERT(same(b[17], 0.64));
      TS_ASSERT(same(b[18], 0.36));
      TS_ASSERT(same(b[19], 0.00));

      TS_ASSERT(same(b[20], 0.00));
      TS_ASSERT(same(b[21], 0.32))
      TS_ASSERT(same(b[22], 0.48));
      TS_ASSERT(same(b[23], 0.00));
      TS_ASSERT_EQUALS(b[24], 0.0);

      TS_ASSERT(same(b[25], 0.04));
      TS_ASSERT(same(b[26], 0.16))
      TS_ASSERT(same(b[27], 1.00));
      TS_ASSERT_EQUALS(b[28], 0.0);
      TS_ASSERT_EQUALS(b[29], 0.0);
    }
  }
};

#endif /* NUMBO_DETAIL_BSPLINE_1D_NU_T_H_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
