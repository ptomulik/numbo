/*
 * @COPYRIGHT@
 * Licensed under MIT license (LICENSE.txt).
 */

// numbo/detail/opencl_c_substitute.hpp

/** // doc: numbo/detail/opencl_c_substitute.hpp {{{
 * \file numbo/detail/opencl_c_substitute.hpp
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_DETAIL_OPENCL_C_SUBSTITUTE_HPP_INCLUDED
#define NUMBO_DETAIL_OPENCL_C_SUBSTITUTE_HPP_INCLUDED

namespace Numbo { namespace Detail {
/** // doc: get_global_id() {{{
 * \todo Write documentation
 */ // }}}
constexpr inline size_t
get_global_id(unsigned int)
{
  return 0;
}
/** // doc: get_global_size() {{{
 * \todo Write documentation
 */ // }}}
constexpr inline size_t
get_global_size(unsigned int)
{
  return 1;
}
} } // end namespace Numbo::Detail

#endif /* NUMBO_DETAIL_OPENCL_C_SUBSTITUTE_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
