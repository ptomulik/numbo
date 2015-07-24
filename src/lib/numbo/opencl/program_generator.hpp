/*
 * @COPYRIGHT@
 * Licensed under MIT license (LICENSE.txt).
 */

// numbo/unit.hpp

/** // doc: numbo/unit.hpp {{{
 * \file numbo/unit.hpp
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_PROGRAM_GENERATOR_HPP_INCLUDED
#define NUMBO_PROGRAM_GENERATOR_HPP_INCLUDED

#include <clxx/cl/program_lazy_generator.hpp>

namespace numbo { namespace opencl {
/** // doc: program_generator {{{
 * \todo Write documentation
 */ // }}}
class program_generator
  : public clxx::program_lazy_generator
{
public:
  /** // doc: program_namespace() {{{
   * \todo Write documentation
   */ // }}}
  virtual std::string program_namespace() const
  { return "numbo::opencl::programs"; }
  /** // doc: program_dir() {{{
   * \todo Write documentation
   */ // }}}
  virtual std::string program_dir() const
  { return "numbo/opencl/programs"; }
  /** // doc: generate_program_header() {{{
   * \todo Write documentation
   */ // }}}
  virtual void
  generate_program_header(std::string& src, clxx::context const& context) const
  {
    (void)context;
    src.append(line_directive(1)); src.append("\n");
  }
  /** // doc: generate_program_body() {{{
   * \todo Write documentation
   */ // }}}
  virtual void
  generate_program_body(std::string& src, clxx::context const& context) const = 0;
  /** // doc: generate_program_footer() {{{
   * \todo Write documentation
   */ // }}}
  virtual void
  generate_program_footer(std::string& src, clxx::context const& context) const
  {
    (void)src; 
    (void)context;
  }
  /** // doc: estimated_program_size() {{{
   * \todo Write documentation
   */ // }}}
  virtual size_t
  estimated_program_size(clxx::context const& context) const
  {
    (void)context;
    return 0;
  }
  /** // doc: generate_program_header() {{{
   * \todo Write documentation
   */ // }}}
  virtual void
  generate_program_source(std::string& src, clxx::context const& context) const
  {
    size_t size = this->estimated_program_size(context);
    if(size != 0)
      src.reserve(src.size() + size);

    generate_program_header(src, context);
    generate_program_body(src, context);
    generate_program_footer(src, context);
  }
};
} } // end namespace numbo::opencl

#endif /* NUMBO_PROGRAM_GENERATOR_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
