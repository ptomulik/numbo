/*
 * @COPYRIGHT@
 * Licensed under MIT license (LICENSE.txt).
 */

// numbo/opencl/program_lazy_generator.hpp

/** // doc: numbo/opencl/program_lazy_generator.hpp {{{
 * \file numbo/opencl/program_lazy_generator.hpp
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_OPENCL_PROGRAM_LAZY_GENERATOR_HPP_INCLUDED
#define NUMBO_OPENCL_PROGRAM_LAZY_GENERATOR_HPP_INCLUDED

#include <clxx/cl/program.hpp>
#include <clxx/cl/context.hpp>
#include <map>

namespace numbo { namespace opencl {
/** // doc: program_lazy_generator {{{
 * \todo Write documentation
 */ // }}}
template<class Derived>
class program_lazy_generator
{
private:
  mutable std::map<clxx::context, clxx::program> _programs;
protected:
  /** // doc: program_lazy_generator() {{{
   * \todo Write documentation
   */ // }}}
  program_lazy_generator() {}
  /** // doc: generate {{{
   * \todo Write documentation
   */ // }}}
  clxx::program generate(clxx::context const& context) const
  {
    clxx::program_source src;
    this->Derived::generate_program_source(src);
    return clxx::program(context, clxx::program_sources{src});
  }
public:
  /** // doc: program_lazy_generator(program_lazy_generator const&) {{{
   * \todo Write documentation
   */ // }}}
  program_lazy_generator(program_lazy_generator const&) = delete;
  /** // doc: operator=(program_lazy_generator const&) {{{
   * \todo Write documentation
   */ // }}}
  void operator=(program_lazy_generator const&) = delete;
  /** // doc: instance() {{{
   * \todo Write documentation
   */ // }}}
  static Derived&
  instance()
  {
    static Derived _instance;
    return _instance;
  }
  /** // doc: get_program(context) {{{
   * \todo Write documentation
   */ // }}}
  clxx::program get(clxx::context const& context, bool force_generate = false) const
  {
    if(!force_generate)
      {
        try {
          return _programs.at(context);
        } catch(std::out_of_range const&) {
          return _programs[context] = this->Derived::generate(context);
        }
      }
    else
      return _programs[context] = this->Derived::generate(context);
  }
  /** // doc: erase(context) {{{
   * \todo Write documentation
   */ // }}}
  size_t erase(clxx::context const& context) const
  { return _programs.erase(context); }
  /** // doc: clear() {{{
   * \todo Write documentation
   */ // }}}
  void clear() const
  { _programs.clear(); }
};
} } // end namespace numbo::opencl

#endif /* NUMBO_OPENCL_PROGRAM_LAZY_GENERATOR_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
