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

#include <numbo/opencl/util/type_to_string.hpp>
#include <numbo/opencl/program_generator.hpp>

namespace numbo { namespace opencl { namespace kernels {
#if 0
template<typename SourceT>
void generate_ppfun_1d_nu_ppform_eval(SourceT& src, std::string const& floating_string)
{
  // return type
  src.append("double\n");
  // name
  src.append("ppfun_1d_nu_ppform_eval");
  // arguments
  src.append("(");
  src.append("int k, ");
  src.append("int j, ");
  src.append(floating_string); src.append("* c, ");
  src.append(floating_string); src.append(" h");
  src.append(")\n");
  // end of arguments
  // body
  src.append("{\n");
  src.append("  "); src.append(floating_string); src.append("  v = 0;\n");
  src.append("  int m, d = k - j;\n");
  src.append("  for(m = k - 1; m >= j; --m, --d)\n");
  src.append("    v = (v/d)*h + c[m];\n");
  src.append("  return v;\n");
  src.append("}\n");
  // end of body
}
#endif
template<typename SourceT> void
generate_ppfun_1d_nu_search_interval_lin(SourceT& src,
                                         std::string const& floating,
                                         std::string const& integral)
{
  // prototype
  src.append("__kernel void\n");
  src.append("search_interval_lin("); src.append(floating); src.append(" point,\n");
  src.append("                    "); src.append(integral); src.append(" num_intervals,\n");
  src.append("     __global const "); src.append(floating); src.append("* breaks,\n");
  src.append("           __global "); src.append(integral); src.append("* index)\n");
  src.append("{\n");
  src.append("  size_t id0 = get_global_id(0);\n");
  src.append("  size_t nd0 = get_global_size(0);\n");
  src.append("  for(size_t j = id0; j < num_intervals; j += nd0) {\n");
  src.append("    if(breaks[j] <= point && point < breaks[j+1])\n");
  src.append("      *index = j;\n");
  src.append("  }\n");
  src.append("}\n");
}

template<typename SourceT> void
generate_ppfun_1d_nu_search_interval_lin_cuda_cc1(SourceT& src,
                                                  std::string const& floating,
                                                  std::string const& integral)
{
  // prototype
  src.append("__kernel void\n");
  src.append("search_interval_lin_cuda_cc1("); src.append(floating); src.append(" point,\n");
  src.append("                             "); src.append(integral); src.append(" num_intervals,\n");
  src.append("              __global const "); src.append(floating); src.append("* breaks,\n");
  src.append("                    __global "); src.append(integral); src.append("* index,\n");
  src.append("                     __local "); src.append(floating); src.append("* tile)\n");
  src.append("{\n");
  src.append("#define SEARCH_INTERVAL_LIN_CUDA_CC1_OVERLAP 16\n");
  src.append("  size_t nd0loc = get_local_size(0) - SEARCH_INTERVAL_LIN_CUDA_CC1_OVERLAP;\n");
  src.append("  size_t id0loc = get_local_id(0);\n");
  src.append("  size_t nd0 = get_num_groups(0)*nd0loc;\n");
  src.append("  size_t id0 = get_group_id(0)*nd0loc + id0loc;\n");
  src.append("  "); src.append(integral); src.append(" n = num_intervals + id0loc;\n");
  src.append("  for("); src.append(integral); src.append(" j = id0; j < n; j += nd0) {\n");
  src.append("    tile[id0loc] = (j <= num_intervals) ? breaks[j] : 0;\n");
  src.append("    barrier(CLK_LOCAL_MEM_FENCE);\n");
  src.append("    if((id0loc < nd0loc) && tile[id0loc] <= point && point < tile[id0loc+1])\n");
  src.append("      *index = j;\n");
  src.append("  }\n");
  src.append("}\n");
}

template<typename SourceT> void
generate_ppfun_1d_nu_search_interval_dca(SourceT& src,
                                         std::string const& floating,
                                         std::string const& integral)
{
  // prototype
  src.append("__kernel void\n");
  src.append("search_interval_dca("); src.append(floating); src.append(" point,\n");
  src.append("                    "); src.append(integral); src.append(" num_intervals,\n");
  src.append("     __global const "); src.append(floating); src.append("* breaks,\n");
  src.append("           __global "); src.append(integral); src.append("* index,\n");
  src.append("                    "); src.append(integral); src.append(" dist,\n");
  src.append("                    "); src.append(integral); src.append(" dist_next)\n");
  src.append("{\n");
  src.append("  size_t id0 = get_global_id(0);\n");
  src.append("  "); src.append(integral); src.append(" left = *index;\n");
  src.append("  "); src.append(integral); src.append(" right = min(left + dist, num_intervals);\n");
  src.append("  "); src.append(integral); src.append(" left_next = min(left + dist_next*id0, right);\n");
  src.append("  "); src.append(integral); src.append(" right_next = min(left + dist_next*(id0+1), right);\n");
  src.append("  if(breaks[left_next] <= point && point < breaks[right_next])\n");
  src.append("    *index = left_next;\n");
  src.append("}\n");
}

template<typename FloatingT, typename IntegralT = cl_uint>
class ppfun_1d_nu
  : program_generator< ppfun_1d_nu<FloatingT, IntegralT> >
{
public:
  typedef program_generator< ppfun_1d_nu<FloatingT, IntegralT> > base_type;
  using base_type::get;

  static constexpr size_t program_source_estimated_size = 1800ul;
  using FloatingToS = util::type_to_string<FloatingT, util::floating_type_tag>;
  using IntegralToS = util::type_to_string<IntegralT, util::integral_type_tag>;

  static void generate_program_source(clxx::program_source& src)
  {
    const std::string floating = FloatingToS::apply();
    const std::string integral = IntegralToS::apply();
    src.reserve(src.size() + program_source_estimated_size);
    generate_ppfun_1d_nu_search_interval_lin(src, floating, integral);
    generate_ppfun_1d_nu_search_interval_lin_cuda_cc1(src, floating, integral);
    generate_ppfun_1d_nu_search_interval_dca(src, floating, integral);
  }
};

} } } // end namespace numbo::opencl::kernels

#endif /* NUMBO_OCL_KERNELS_PPFUN_1D_NU_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
