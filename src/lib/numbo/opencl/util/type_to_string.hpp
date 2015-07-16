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

#include <clxx/types.hpp>
#include <string>

namespace numbo { namespace opencl { namespace util {

struct floating_type_tag { };
struct integral_type_tag { };

template<typename T> struct type_to_string_dispatch;

// integral types
template<>
  struct type_to_string_dispatch<cl_char>
  { typedef integral_type_tag type; };
template<>
  struct type_to_string_dispatch<cl_short>
  { typedef integral_type_tag type; };
template<>
  struct type_to_string_dispatch<cl_int>
  { typedef integral_type_tag type; };
template<>
  struct type_to_string_dispatch<cl_long>
  { typedef integral_type_tag type; };
// unsigned integral types
template<>
  struct type_to_string_dispatch<cl_uchar>
  { typedef integral_type_tag type; };
template<>
  struct type_to_string_dispatch<cl_ushort>
  { typedef integral_type_tag type; };
template<>
  struct type_to_string_dispatch<cl_uint>
  { typedef integral_type_tag type; };
template<>
  struct type_to_string_dispatch<cl_ulong>
  { typedef integral_type_tag type; };
// floating-point types
template<>
  struct type_to_string_dispatch<cl_float>
  { typedef floating_type_tag type; };
template<>
  struct type_to_string_dispatch<cl_double>
  { typedef floating_type_tag type; };

/** // doc: type_to_string {{{
 * \todo Write documentation
 */ // }}}
template<typename T, typename Tag = typename type_to_string_dispatch<T>::type>
  struct type_to_string;

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template<>
  struct type_to_string<cl_char, integral_type_tag>
  { static std::string apply() { return "char"; } };
template<>
  struct type_to_string<cl_short, integral_type_tag>
  { static std::string apply() { return "short"; } };
template<>
  struct type_to_string<cl_int, integral_type_tag>
  { static std::string apply() { return "int"; } };
template<>
  struct type_to_string<cl_long, integral_type_tag>
  { static std::string apply() { return "long"; } };
// unsigned types
template<>
  struct type_to_string<cl_uchar, integral_type_tag>
  { static std::string apply() { return "uchar"; } };
template<>
  struct type_to_string<cl_ushort, integral_type_tag>
  { static std::string apply() { return "ushort"; } };
template<>
  struct type_to_string<cl_uint, integral_type_tag>
  { static std::string apply() { return "uint"; } };
template<>
  struct type_to_string<cl_ulong, integral_type_tag>
  { static std::string apply() { return "ulong"; } };
// floating-point types
template<>
  struct type_to_string<cl_float, floating_type_tag>
  { static std::string apply() { return "float"; } };
template<>
  struct type_to_string<cl_double, floating_type_tag>
  { static std::string apply() { return "double"; } };
template<>
  struct type_to_string<cl_half, floating_type_tag>
  { static std::string apply() { return "half"; } };
/** \endcond */
}}} // end namespace numbo::opencl::util

#endif /* NUMBO_OPENCL_UTIL_TYPE_TO_STRING_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
