// Copyright (C) 2014, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** // doc: numbo/bspline_1d_nu_interp_spcol1.cpp {{{
 * \file numbo/bspline_1d_nu_interp_spcol1.cpp
 * \example numbo/bspline_1d_nu_interp_spcol1.cpp
 * \brief Usage example for TODO:
 */ // }}}

// [Code]
#include <numbo/detail/bspline_1d_nu.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  using namespace Numbo::Detail;

  const size_t k = 4;
  const size_t n = 4;
  const size_t md = 2*(k-1);
  const size_t mb = 2*(k-1) + 1;
  double t[n+k] = { 0.0, 0.0, 0.0, 0.0,                       1.0, 1.0, 1.0, 1.0 };
  double tau[n] = {                     0.0, 0.4, 0.6, 1.0 };
  double d[md * n];
  double b[mb * n] = { 0.0 };

  std::cout << std::setprecision(10) << std::fixed;

  size_t res = bspline_1d_nu_interp_spcol(k, n, t, tau, md, d, mb, b);
 
  for(size_t i = 0; i < mb; ++i)
    {
      for(size_t j = 0; j < n; ++j)
        {
          std::cout << "\t" << b[i + mb*j];
        }
      std::cout << std::endl;
    }
  std::cout << res << std::endl;
  return 0;
}
// [Code]

/* [Output]
	0.0000000000	0.0000000000	0.0000000000	0.0000000000
	0.0000000000	0.0000000000	0.0000000000	0.0640000000
	0.0000000000	0.0000000000	0.2880000000	0.2160000000
	1.0000000000	0.4320000000	0.4320000000	1.0000000000
	0.2160000000	0.2880000000	0.0000000000	0.0000000000
	0.0640000000	0.0000000000	0.0000000000	0.0000000000
	0.0000000000	0.0000000000	0.0000000000	0.0000000000
4
   [Output] */

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
