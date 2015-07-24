/*
 * @COPYRIGHT@
 * Licensed under MIT license (LICENSE.txt).
 */

// numbo/unit.hpp

/** // doc: numbo/unit.hpp {{{
 * \file numbo/unit.hpp
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_OPENCL_STATIC_PROGRAM_GENERATOR_HPP_INCLUDED
#define NUMBO_OPENCL_STATIC_PROGRAM_GENERATOR_HPP_INCLUDED

#include<numbo/opencl/program_generator.hpp>

namespace numbo { namespace opencl {
/** // doc: static_program_generator {{{
 * \todo Write documentation
 */ // }}}
template<class Derived>
class static_program_generator
  : public program_generator
{
public:
  /** // doc: static_program_namespace() {{{
   * \todo Write documentation
   */ // }}}
  inline static std::string const&
  static_program_namespace()
  {
    static const std::string s{"numbo::opencl::programs"};
    return s;
  }
  /** // doc: static_program_name() {{{
   * \todo Write documentation
   */ // }}}
  inline static std::string const&
  static_program_full_name()
  {
    static const std::string s{static_program_namespace() + "::" + Derived::static_program_name()};
    return s;
  }
  /** // doc: static_program_name() {{{
   * \todo Write documentation
   */ // }}}
  inline static std::string const&
  static_program_file_suffix()
  {
    static const std::string s{".cl"};
    return s;
  }
  /** // doc: static_program_dir() {{{
   * \todo Write documentation
   */ // }}}
  inline static std::string const&
  static_program_dir()
  {
    static const std::string s{"numbo/opencl/programs"};
    return s;
  }
  /** // doc: static_program_name() {{{
   * \todo Write documentation
   */ // }}}
  inline static std::string const&
  static_program_path()
  {
    static const std::string s{static_program_dir() + "/" + Derived::static_program_file()};
    return s;
  }
  /** // doc: estimated_program_size() {{{
   * \todo Write documentation
   */ // }}}
  virtual size_t
  estimated_program_size(clxx::context const& context) const
  { return Derived::static_estimated_program_size(context); }
  /** // doc: program_name() {{{
   * \todo Write documentation
   */ // }}}
  virtual std::string
  program_name() const
  { return Derived::static_program_name(); }
  /** // doc: program_namespace() {{{
   * \todo Write documentation
   */ // }}}
  virtual std::string
  program_namespace() const
  { return static_program_namespace(); }
  /** // doc: program_full_name() {{{
   * \todo Write documentation
   */ // }}}
  virtual std::string
  program_full_name() const
  { return static_program_full_name(); }
  /** // doc: program_file_suffix() {{{
   * \todo Write documentation
   */ // }}}
  virtual std::string
  program_file_suffix() const
  { return static_program_file_suffix(); }
  /** // doc: program_file() {{{
   * \todo Write documentation
   */ // }}}
  virtual std::string
  program_file() const
  { return Derived::static_program_file(); }
  /** // doc: program_dir() {{{
   * \todo Write documentation
   */ // }}}
  virtual std::string
  program_dir() const
  { return static_program_dir(); }
  /** // doc: program_path() {{{
   * \todo Write documentation
   */ // }}}
  virtual std::string
  program_path() const
  { return static_program_path(); }
};
} } // end namespace numbo::opencl

#endif /* NUMBO_OPENCL_STATIC_PROGRAM_GENERATOR_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
