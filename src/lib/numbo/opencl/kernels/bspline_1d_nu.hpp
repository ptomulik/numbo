/*
 * @COPYRIGHT@
 * Licensed under MIT license (LICENSE.txt).
 */

// numbo/opencl/kernels/bspline_1d_nu.hpp

/** // doc: numbo/opencl/kernels/bspline_1d_nu.hpp {{{
 * \file numbo/opencl/kernels/bspline_1d_nu.hpp
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_OCL_KERNELS_BSPLINE_1D_NU_HPP_INCLUDED
#define NUMBO_OCL_KERNELS_BSPLINE_1D_NU_HPP_INCLUDED

#include <string>

namespace numbo { namespace opencl { namespace kernels {

template<typename StringT>
void generate_bspline_1d_nu_1p_deltas(StringT& src, std::string const& numeric_string)
{
  // return type
  src.append("__kernel void\n");
  // name
  src.append("bspline_1d_nu_1p_deltas");
  // arguments
  src.append("(");
  src.append("unsigned int k, ");
  src.append("__global const "); src.append(numeric_string); src.append("* t, ");
  src.append("int i, ");
  src.append(numeric_string); src.append(" x, ");
  src.append("__global "); src.append(numeric_string); src.append("* dkl, ");
  src.append("__global "); src.append(numeric_string); src.append("* dkr");
  src.append(")\n");
  // end of arguments
  // body
  src.append("{\n");
  src.append("  uint sm1 = get_local_id(0); /* sm1 := s - 1 */\n");
  src.append("  dkl[sm1] = x - t[i - k + 2 + sm1];\n");
  src.append("  dkr[sm1] = x - t[i + 1 + sm1];\n");
  src.append("}\n");
  // end of body
}

template<typename StringT>
void generate_bspline_1d_nu_np_deltas(StringT& src, std::string const& numeric_string)
{
  // return type
  src.append("__kernel void\n");
  // name
  src.append("bspline_1d_nu_np_deltas");
  // arguments
  src.append("(");
  src.append("unsigned int k, ");
  src.append("__global const "); src.append(numeric_string); src.append("* t, ");
  src.append("int i, ");
  src.append(numeric_string); src.append(" x, ");
  src.append("__global "); src.append(numeric_string); src.append("* dkl, ");
  src.append("__global "); src.append(numeric_string); src.append("* dkr,");
  src.append(")\n");
  // end of arguments
  // body
  src.append("{\n");
  src.append("  uint loc_id = get_global_id(1); /* loc_id :=  */\n");
  src.append("  dkl[loc_id] = x - t[i - k + 2 + loc_id];\n");
  src.append("  dkr[loc_id] = x - t[i + 1 + loc_id];\n");
  src.append("}\n");
  // end of body
}

} } } // end namespace numbo::opencl::kernels

#endif /* NUMBO_OCL_KERNELS_BSPLINE_1D_NU_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
