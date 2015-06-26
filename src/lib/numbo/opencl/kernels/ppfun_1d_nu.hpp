/*
 * @COPYRIGHT@
 * Licensed under MIT license (LICENSE.txt).
 */

// numbo/opencl/kernels/ppfun_1d_nu.hpp

/** // doc: numbo/opencl/kernels/ppfun_1d_nu.hpp {{{
 * \file numbo/opencl/kernels/ppfun_1d_nu.hpp
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_OCL_KERNELS_PPFUN_1D_NU_HPP_INCLUDED
#define NUMBO_OCL_KERNELS_PPFUN_1D_NU_HPP_INCLUDED

#include <string>

namespace numbo { namespace opencl { namespace kernels {

template<typename StringT>
void generate_ppfun_1d_nu_ppform_eval(StringT& src, std::string const& numeric_string)
{
  // return type
  src.append("double\n");
  // name
  src.append("ppfun_1d_nu_ppform_eval");
  // arguments
  src.append("(");
  src.append("int k, ");
  src.append("int j, ");
  src.append(numeric_string); src.append("* c, ");
  src.append(numeric_string); src.append(" h");
  src.append(")\n");
  // end of arguments
  // body
  src.append("{\n");
  src.append("  "); src.append(numeric_string); src.append("  v = 0;\n");
  src.append("  int m, d = k - j;\n");
  src.append("  for(m = k - 1; m >= j; --m, --d)\n");
  src.append("    v = (v/d)*h + c[m];\n");
  src.append("  return v;\n");
  src.append("}\n");
  // end of body
}
} } } // end namespace numbo::opencl::kernels

#endif /* NUMBO_OCL_KERNELS_PPFUN_1D_NU_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
