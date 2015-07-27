/*
 * @COPYRIGHT@
 * Licensed under MIT license (LICENSE.txt).
 */

// numbo/opencl/programs/search_interval.hpp

/** // doc: numbo/opencl/programs/search_interval.hpp {{{
 * \file numbo/opencl/programs/search_interval.hpp
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_OCL_PROGRAMS_SEARCH_INTERVAL_HPP_INCLUDED
#define NUMBO_OCL_PROGRAMS_SEARCH_INTERVAL_HPP_INCLUDED

#include <numbo/opencl/util/type_to_string.hpp>
#include <numbo/opencl/static_program_generator.hpp>

namespace numbo { namespace opencl { namespace programs {
template<typename SourceT> void
generate_search_interval_lin(SourceT& src, std::string const& value,
                                           std::string const& index)
{
  // prototype
  src.append("__kernel void\n");
  src.append("search_interval_lin("); src.append(value); src.append(" point,\n");
  src.append("                    "); src.append(index); src.append(" num_intervals,\n");
  src.append("     __global const "); src.append(value); src.append("* breaks,\n");
  src.append("           __global "); src.append(index); src.append("* index)\n");
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
generate_search_interval_lin_cuda_cc1(SourceT& src, std::string const& value,
                                                    std::string const& index)
{
  // prototype
  src.append("__kernel void\n");
  src.append("search_interval_lin_cuda_cc1("); src.append(value); src.append(" point,\n");
  src.append("                             "); src.append(index); src.append(" num_intervals,\n");
  src.append("              __global const "); src.append(value); src.append("* breaks,\n");
  src.append("                    __global "); src.append(index); src.append("* index,\n");
  src.append("                     __local "); src.append(value); src.append("* tile)\n");
  src.append("{\n");
  src.append("#define SEARCH_INTERVAL_LIN_CUDA_CC1_OVERLAP 16\n");
  src.append("  size_t nd0loc = get_local_size(0) - SEARCH_INTERVAL_LIN_CUDA_CC1_OVERLAP;\n");
  src.append("  size_t id0loc = get_local_id(0);\n");
  src.append("  size_t nd0 = get_num_groups(0)*nd0loc;\n");
  src.append("  size_t id0 = get_group_id(0)*nd0loc + id0loc;\n");
  src.append("  "); src.append(index); src.append(" n = num_intervals + id0loc;\n");
  src.append("  for("); src.append(index); src.append(" j = id0; j < n; j += nd0) {\n");
  src.append("    tile[id0loc] = (j <= num_intervals) ? breaks[j] : 0;\n");
  src.append("    barrier(CLK_LOCAL_MEM_FENCE);\n");
  src.append("    if((id0loc < nd0loc) && tile[id0loc] <= point && point < tile[id0loc+1])\n");
  src.append("      *index = j;\n");
  src.append("  }\n");
  src.append("}\n");
}

template<typename SourceT> void
generate_search_interval_dca(SourceT& src, std::string const& value,
                                           std::string const& index)
{
  // prototype
  src.append("__kernel void\n");
  src.append("search_interval_dca("); src.append(value); src.append(" point,\n");
  src.append("                    "); src.append(index); src.append(" num_intervals,\n");
  src.append("     __global const "); src.append(value); src.append("* breaks,\n");
  src.append("           __global "); src.append(index); src.append("* index,\n");
  src.append("                    "); src.append(index); src.append(" dist,\n");
  src.append("                    "); src.append(index); src.append(" dist_next)\n");
  src.append("{\n");
  src.append("  "); src.append(index); src.append(" id0 = get_global_id(0);\n");
  src.append("  "); src.append(index); src.append(" left = *index;\n");
  src.append("  "); src.append(index); src.append(" right = min(left + dist, num_intervals);\n");
  src.append("  "); src.append(index); src.append(" left_next = min(left + dist_next*id0, right);\n");
  src.append("  "); src.append(index); src.append(" right_next = min(left + dist_next*(id0+1), right);\n");
  src.append("  if(breaks[left_next] <= point && point < breaks[right_next])\n");
  src.append("    *index = left_next;\n");
  src.append("}\n");
}

template<typename ValueT, typename IndexT>
class search_interval
  : public static_program_generator<search_interval<ValueT, IndexT> >
{
  typedef static_program_generator<search_interval<ValueT, IndexT> > Base;
public:
  inline static size_t
  static_estimated_program_size(clxx::context const&)
  { return 1800ul; }

  inline static std::string const&
  static_program_classname()
  {
    static const std::string s{
      "search_interval<" + util::type_to_string<ValueT>::apply() + "," +
                           util::type_to_string<IndexT>::apply() + ">" 
    };
    return s;
  }

  inline static std::string const&
  static_program_file()
  {
    static const std::string s{
      "search_interval__" + util::type_to_string<ValueT>::apply() + "__" +
                            util::type_to_string<IndexT>::apply() + ".cl"
    };
    return s;
  }

  void
  generate_program_body(std::string& src, clxx::context const&) const
  {
    const std::string value = util::type_to_string<ValueT>::apply();
    const std::string index = util::type_to_string<IndexT>::apply();

    generate_search_interval_lin(src, value, index);
    generate_search_interval_lin_cuda_cc1(src, value, index);
    generate_search_interval_dca(src, value, index);
  }
};
} } } // end namespace numbo::opencl::programs

#endif /* NUMBO_OCL_PROGRAMS_SEARCH_INTERVAL_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
