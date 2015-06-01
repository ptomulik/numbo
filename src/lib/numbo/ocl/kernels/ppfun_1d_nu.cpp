/*
 * @COPYRIGHT@
 * Licensed under MIT license (LICENSE.txt).
 */

/** // doc: numbo/ocl/kernels/ppfun_1d_nu.cpp {{{
 * \file numbo/ocl/kernels/ppfun_1d_nu.cpp
 * \todo Write documentation
 */ // }}}
#include <numbo/ocl/kernels/ppfun_1d_nu.hpp>
#include <string>
#include <iostream>

int main()
{
  using namespace Numbo::Ocl::Kernels;
  std::string s;
  generate_ppfun_1d_nu_ppform_eval(s, "double");
  std::cout << s << std::endl;
  return 0;
}
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
