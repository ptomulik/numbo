/*
 * @COPYRIGHT@
 * Licensed under MIT license (LICENSE.txt).
 */

// numbo/opencl/util/type_to_string.hpp

/** // doc: numbo/opencl/util/type_to_string.hpp {{{
 * \file numbo/opencl/util/type_to_string.hpp
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_OPENCL_UTIL_TYPE_TO_STRING_HPP_INCLUDED
#define NUMBO_OPENCL_UTIL_TYPE_TO_STRING_HPP_INCLUDED

#include <clxx/common/types.hpp>
#include <string>

namespace numbo { namespace opencl { namespace util {
/** // doc: type_to_string {{{
 * \todo Write documentation
 */ // }}}
template<typename T/*, typename Tag = typename type_to_string_dispatch<T>::type*/>
  struct type_to_string;

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template<>
  struct type_to_string<cl_char>
  { static std::string apply() { return "char"; } };
template<>
  struct type_to_string<cl_short>
  { static std::string apply() { return "short"; } };
template<>
  struct type_to_string<cl_int>
  { static std::string apply() { return "int"; } };
template<>
  struct type_to_string<cl_long>
  { static std::string apply() { return "long"; } };
// unsigned types
template<>
  struct type_to_string<cl_uchar>
  { static std::string apply() { return "uchar"; } };
template<>
  struct type_to_string<cl_ushort>
  { static std::string apply() { return "ushort"; } };
template<>
  struct type_to_string<cl_uint>
  { static std::string apply() { return "uint"; } };
template<>
  struct type_to_string<cl_ulong>
  { static std::string apply() { return "ulong"; } };
// floating-point types
template<>
  struct type_to_string<cl_float>
  { static std::string apply() { return "float"; } };
template<>
  struct type_to_string<cl_double>
  { static std::string apply() { return "double"; } };
/** \endcond */
}}} // end namespace numbo::opencl::util

#endif /* NUMBO_OPENCL_UTIL_TYPE_TO_STRING_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
