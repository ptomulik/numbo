// @COPYRIGHT@
// Licensed under MIT license (LICENSE.txt)

// numbo/opencl/programs/search_interval.t.h

/** // doc: numbo/opencl/programs/search_interval.t.h {{{
 * \file numbo/opencl/programs/search_interval.t.h
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_OPENCL_PROGRAMS_SEARCH_INTERVAL_T_H_INCLUDED
#define NUMBO_OPENCL_PROGRAMS_SEARCH_INTERVAL_T_H_INCLUDED

#include <cxxtest/TestSuite.h>
#include <numbo/opencl/programs/search_interval.hpp>
#include <clxx/cl/platform_layer.hpp>
#include <clxx/cl/context.hpp>
#include <clxx/cl/kernel.hpp>
#include <iostream>

namespace numbo { namespace opencl { namespace programs { class search_interval_TestSuite; } } }

/** // doc: class numbo::opencl::programs::search_interval_TestSuite {{{
 * \todo Write documentation
 */ // }}}
class numbo::opencl::programs::search_interval_TestSuite : public CxxTest::TestSuite
{
private:
  clxx::context new_context(clxx::device_type_t dev_type = clxx::device_type_t::all) const
  {
    clxx::platform_layer platform_layer{ dev_type };
    clxx::platform platform{ platform_layer.get_platforms()[0] };
    return clxx::context(clxx::make_context_properties(), platform_layer.get_devices(platform));
  }
public:

  void test__generate_search_interval_lin__1()
  {
    std::string src;
    generate_search_interval_lin(src, "float", "uint");
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

  void test__generate_search_interval_lin_cuda_cc1__1()
  {
    std::string src;
    generate_search_interval_lin_cuda_cc1(src, "float", "uint");
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

  void test__generate_search_interval_dca__1()
  {
    std::string src;
    generate_search_interval_dca(src, "float", "uint");
    TS_ASSERT_EQUALS(src,
      "__kernel void\n"
      "search_interval_dca(float point,\n"
      "                    uint num_intervals,\n"
      "     __global const float* breaks,\n"
      "           __global uint* index,\n"
      "                    uint dist,\n"
      "                    uint dist_next)\n"
      "{\n"
      "  uint id0 = get_global_id(0);\n"
      "  uint left = *index;\n"
      "  uint right = min(left + dist, num_intervals);\n"
      "  uint left_next = min(left + dist_next*id0, right);\n"
      "  uint right_next = min(left + dist_next*(id0+1), right);\n"
      "  if(breaks[left_next] <= point && point < breaks[right_next])\n"
      "    *index = left_next;\n"
      "}\n"
    );
  }

  void test__search_interval__generate_source__1()
  {
    const std::string floating = util::type_to_string<cl_float>::apply();
    const std::string integral = util::type_to_string<cl_uint>::apply();

    std::string src1;
    search_interval<cl_float, cl_uint> generator;

    generator.generate_source(src1);

    std::string src2;
    src2.append("#line 1 \"numbo/search_interval__T__float__uint.cl\"\n");
    generate_search_interval_lin(src2, floating, integral);
    generate_search_interval_lin_cuda_cc1(src2, floating, integral);
    generate_search_interval_dca(src2, floating, integral);

    TS_ASSERT(src1.size() <= generator.estimated_program_size());
    TS_ASSERT_EQUALS(src1, src2);
  }

  void test__search_interval__get_program__1()
  {
    search_interval<cl_float, cl_uint> generator;

    clxx::context c{ new_context() };
    clxx::program p1{ generator.get_program(c) };
    clxx::program p2{ generator.get_program(c) };

    TS_ASSERT(p1 == p2); // it shall return same handle
    TS_ASSERT(p1.get_reference_count() >= 3u); // p1, p2 and the memoized program

    clxx::devices devices{p1.get_devices()};
    for(size_t i = 0; i < devices.size(); i++) {
      TS_ASSERT(p1.get_build_status(devices[i]) == clxx::build_status_t::none);
    }

    // try to build
    try {
      clxx::build_program(p1, "");
    } catch(clxx::clerror_no<clxx::status_t::build_program_failure> const&) {
      // just to print out the build log...
      for(size_t i = 0; i < devices.size(); i++) {
        if(clxx::is_error(p1.get_build_status(devices[i]))) {
          TS_FAIL(p1.get_build_log(devices[i]));
        }
      }
    }
  }
};

#endif /* NUMBO_OPENCL_PROGRAMS_SEARCH_INTERVAL_T_H_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
