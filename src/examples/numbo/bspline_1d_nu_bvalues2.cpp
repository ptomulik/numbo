// Copyright (C) 2014, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** // doc: numbo/bspline_1d_nu_bvalues2.cpp {{{
 * \file numbo/bspline_1d_nu_bvalues2.cpp
 * \example numbo/bspline_1d_nu_bvalues2.cpp
 * \brief Usage example for \ref numbo::detail::bspline_1d_nu_bvalues()
 */ // }}}

// [Code]
#include <numbo/detail/bspline_1d_nu.hpp>
#include <vector>
#include <sstream>
#include <iostream>

//! Reads knot coordinates from stdin
size_t read_knots(std::vector<double>& tv)
{
  std::string line;
  std::stringstream ss;
  size_t n = 0;

  while(getline(std::cin, line) && !line.empty())
  {
    double ti;
    std::string dummy;
    ss.clear();
    ss << line; 
    ss >> ti;
    if(!ss.fail())
      {
        tv.push_back(ti);
        ++n;
      }
    ss >> dummy;
  }
  return n;
}

//! Reads evaluation points from stdin
size_t read_points(std::vector<ptrdiff_t>& iv, std::vector<double>& xv)
{
  std::string line;
  std::stringstream ss;
  size_t n = 0;

  while(getline(std::cin, line) && !line.empty())
  {
    ptrdiff_t i;
    double x;
    std::string dummy;
    ss.clear();
    ss << line; 
    ss >> i >> x;
    if(!ss.fail())
      {
        iv.push_back(i);
        xv.push_back(x);
        ++n;
      }
    ss >> dummy;
  }
  return n;
}

//! Reads B-spline order (maximum, and the requested order) from stdin
size_t read_orders(size_t& kmax, size_t& k)
{
  std::string line;
  std::stringstream ss;

  size_t n = 0;
  if(getline(std::cin, line))
    {
      ss << line;
      ss >> kmax >> k;
      if(!ss.fail())
        ++n;
    }
  return n;
}

//! Reads all required values from stdin
int read_input(std::vector<double>& tv, std::vector<ptrdiff_t>& iv,
               std::vector<double>& xv, size_t& kmax, size_t& k)
{
  size_t nknots, npoints;
  size_t norder;



  nknots = read_knots(tv);
  npoints = read_points(iv,xv);
  norder = read_orders(kmax, k);

  if(!nknots)
    {
      std::cerr << "error: couldn't read knots from input" << std::endl;
      return EXIT_FAILURE;
    }
  if(!npoints)
    {
      std::cerr << "error: couldn't read points from input" << std::endl;
      return EXIT_FAILURE;
    }
  if(!norder)
    {
      std::cerr << "error: couldn't read B-spline orders from input" << std::endl;
      return EXIT_FAILURE;
    }
  if(k > kmax)
    {
      std::cerr <<  "error: k > kmax" << std::endl;
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}

// [Main]
int main() {
  using namespace numbo::detail;

  std::vector<double> tv;
  std::vector<ptrdiff_t> iv;
  std::vector<double> xv;
  std::vector<double> dk;
  std::vector<double> b;
  size_t kmax, k;
  int err;

  if((err = read_input(tv, iv, xv, kmax, k)) != EXIT_SUCCESS)
    return err;

  std::cout.precision(30);

  dk.resize(2*(kmax - 1));
  b.resize(k);

  for(size_t n = 0; n != iv.size(); ++n)
    {
      // Determine deltas at x
      bspline_1d_nu_deltas(kmax, tv.cbegin() + iv[n], xv[n], dk.begin());
      // Compute values of the B-spline base functions at x
      bspline_1d_nu_bvalues(kmax, dk.cbegin(), 0, k, b.begin());
      // Print out the computed values
      if(b.size() != 0)
        {
          std::cout << xv[n] << "\t" << b[0];
          for(size_t m = 1; m != b.size(); ++m)
            {
              std::cout << "\t" << b[m];
            }
          std::cout << std::endl;
        }
    }

  return 0;
}
// [Main]
// [Code]

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
