// Copyright (C) 2014, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** // doc: numbo/unit.cpp {{{
 * \file numbo/bspline_1d_nu_bvalues1.cpp
 * \example numbo/bspline_1d_nu_bvalues1.cpp
 * \brief Usage example for \ref Numbo::Detail::bspline_1d_nu_bvalues()
 */ // }}}

// [Code]
#include <numbo/detail/bspline_1d_nu.hpp>
#include <iostream>

// [Main]
int main() {
  using namespace Numbo::Detail;

  //        i =    0,   1,   2,   3,   4,   5
  double t[6] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0}; // knots
  double dk[6];                                 // deltas
  double b[4];                                  // B-splines

  // Determine B-splines (base functions) of 4-th order at point x = 2.3
  bspline_1d_nu_deltas(4, t+2, 2.3, dk);
  bspline_1d_nu_bvalues(4, dk, 0, 4, b);
  
  std::cout << "B_j(x): " << b[0] << ", "
                          << b[1] << ", "
                          << b[2] << ", "
                          << b[3] << std::endl;
  std::cout << "sum: " << b[0] + b[1] + b[2] + b[3] << std::endl;

  return 0;
}
// [Main]
// [Code]

/* [Output]
B_j(x): 0.0571667, 0.590167, 0.348167, 0.0045
sum: 1
  [Output] */

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
