// @COPYRIGHT@
// Licensed under MIT license (LICENSE.txt)

// numbo/opencl/kernels/ppfun_1d_nu.t.h

/** // doc: numbo/opencl/kernels/ppfun_1d_nu.t.h {{{
 * \file numbo/opencl/kernels/ppfun_1d_nu.t.h
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_OPENCL_KERNELS_PPFUN_1D_NU_T_H_INCLUDED
#define NUMBO_OPENCL_KERNELS_PPFUN_1D_NU_T_H_INCLUDED

#include <cxxtest/TestSuite.h>
#include <numbo/opencl/kernels/ppfun_1d_nu.hpp>

namespace numbo { namespace opencl { namespace kernels { class ppfun_1d_nu_TestSuite; } } }

/** // doc: class numbo::opencl::kernels::ppfun_1d_nu_TestSuite {{{
 * \todo Write documentation
 */ // }}}
class numbo::opencl::kernels::ppfun_1d_nu_TestSuite : public CxxTest::TestSuite
{
public:

  void test__generate_ppfun_1d_nu_search_interval_lin__1()
  {
    std::string src;
    generate_ppfun_1d_nu_search_interval_lin(src, "float", "uint");
    TS_ASSERT_EQUALS(src,
      "__kernel void\n"
      "search_interval_lin(float point,\n"
      "                    uint num_intervals,\n"
      "     __global const float* breaks,\n"
      "           __global uint* index)\n"
      "{\n"
      "  size_t id0 = get_global_id(0);\n"
      "  size_t nd0 = get_global_size(0);\n"
      "  for(size_t j = id0; j < num_intervals; j += nd0) {\n"
      "    if(breaks[j] <= point && point < breaks[j+1])\n"
      "      *index = j;\n"
      "  }\n"
      "}\n"
    );
  }

  void test__generate_ppfun_1d_nu_search_interval_lin_cuda_cc1__1()
  {
    std::string src;
    generate_ppfun_1d_nu_search_interval_lin_cuda_cc1(src, "float", "uint");
    TS_ASSERT_EQUALS(src,
      "__kernel void\n"
      "search_interval_lin_cuda_cc1(float point,\n"
      "                             uint num_intervals,\n"
      "              __global const float* breaks,\n"
      "                    __global uint* index,\n"
      "                     __local float* tile)\n"
      "{\n"
      "#define SEARCH_INTERVAL_LIN_CUDA_CC1_OVERLAP 16\n"
      "  size_t nd0loc = get_local_size(0) - SEARCH_INTERVAL_LIN_CUDA_CC1_OVERLAP;\n"
      "  size_t id0loc = get_local_id(0);\n"
      "  size_t nd0 = get_num_groups(0)*nd0loc;\n"
      "  size_t id0 = get_group_id(0)*nd0loc + id0loc;\n"
      "  uint n = num_intervals + id0loc;\n"
      "  for(uint j = id0; j < n; j += nd0) {\n"
      "    tile[id0loc] = (j <= num_intervals) ? breaks[j] : 0;\n"
      "    barrier(CLK_LOCAL_MEM_FENCE);\n"
      "    if((id0loc < nd0loc) && tile[id0loc] <= point && point < tile[id0loc+1])\n"
      "      *index = j;\n"
      "  }\n"
      "}\n"
    );
  }

  void test__generate_ppfun_1d_nu_search_interval_dca__1()
  {
    std::string src;
    generate_ppfun_1d_nu_search_interval_dca(src, "float", "uint");
    TS_ASSERT_EQUALS(src,
      "__kernel void\n"
      "search_interval_dca(float point,\n"
      "                    uint num_intervals,\n"
      "     __global const float* breaks,\n"
      "           __global uint* index,\n"
      "                    uint dist,\n"
      "                    uint dist_next)\n"
      "{\n"
      "  size_t id0 = get_global_id(0);\n"
      "  uint left = *index;\n"
      "  uint right = min(left + dist, num_intervals);\n"
      "  uint left_next = min(left + dist_next*id0, right);\n"
      "  uint right_next = min(left + dist_next*(id0+1), right);\n"
      "  if(breaks[left_next] <= point && point < breaks[right_next])\n"
      "    *index = left_next;\n"
      "}\n"
    );
  }

  void test__ppfun_1d_nu__generate_program_source__1()
  {
    const std::string floating = util::type_to_string<cl_float, util::floating_type_tag>::apply();
    const std::string integral = util::type_to_string<cl_uint, util::integral_type_tag>::apply();

    std::string src1;
    std::string src2;

    generate_ppfun_1d_nu_search_interval_lin(src2, floating, integral);
    generate_ppfun_1d_nu_search_interval_lin_cuda_cc1(src2, floating, integral);
    generate_ppfun_1d_nu_search_interval_dca(src2, floating, integral);

    //
    ppfun_1d_nu<cl_float, cl_uint>::instance().generate_program_source(src1);
    TS_ASSERT(src1.size() <= (ppfun_1d_nu<cl_float, cl_uint>::program_source_estimated_size));
    TS_ASSERT_EQUALS(src1, src2);
  }

  void test__ppfun_1d_nu__get__1()
  {
  }
};

#endif /* NUMBO_OPENCL_KERNELS_PPFUN_1D_NU_T_H_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
