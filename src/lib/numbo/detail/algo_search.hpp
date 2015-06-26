/*
 * @COPYRIGHT@
 * Licensed under MIT license (LICENSE.txt).
 */

// numbo/detail/algo_search.hpp.hpp

/** // doc: numbo/detail/algo_search.hpp.hpp {{{
 * \file numbo/detail/algo_search.hpp.hpp
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_DETAIL_ALGO_SEARCH_HPP_INCLUDED
#define NUMBO_DETAIL_ALGO_SEARCH_HPP_INCLUDED

#include <numbo/detail/opencl_c_substitute.hpp>
#include <iterator>

namespace numbo { namespace detail {

template<typename SeqIter, typename T>
void algo_search_linear(int n, SeqIter seq, T x, int* pos)
{
  int i;
  int id = get_global_id(0);
  int np = get_global_size(0);
  if(x < seq[0])
    {
      *pos = -1;
      return;
    }
  if(x >= seq[n-1])
    {
      *pos = n-1;
      return;
    }

  for(i = id; i < n-1; i += np)
    {
      if(seq[i] <= x && x < seq[i+1])
        *pos = i;
    }
}

} } // end namespace numbo::detail

#endif /* NUMBO_DETAIL_ALGO_SEARCH_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
