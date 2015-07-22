/*
 * @COPYRIGHT@
 * Licensed under MIT license (LICENSE.txt).
 */

// numbo/opencl/env.hpp

/** // doc: numbo/opencl/env.hpp {{{
 * \file numbo/opencl/env.hpp
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_OPENCL_ENV_HPP_INCLUDED
#define NUMBO_OPENCL_ENV_HPP_INCLUDED

#include <numbo/opencl/program_generator.hpp>
#include <clxx/cl/context.hpp>
#include <stack>
//#include <vector>
#include <string>
#include <memory>
#include <map>

namespace numbo { namespace opencl {
/** // doc: env {{{
 * \todo Write documentation
 */ // }}}
class env
{
public:
  /** // doc: programs_map_t {{{
   * \todo Write documentation
   */ // }}}
  typedef std::map<std::string, std::unique_ptr<program_generator> > programs_map_t;
  /** // doc: build_options_stack_t {{{
   * \todo Write documentation
   */ // }}}
  typedef std::stack<std::string> build_options_stack_t;
  /** // doc: build_options_map_t {{{
   * \todo Write documentation
   */ // }}}
  typedef std::map<clxx::context, build_options_stack_t> build_options_map_t;
public:
  /** // doc: env() {{{
   * \todo Write documentation
   */ // }}}
  inline env()
    : _build_options()
  { 
    // default options for default context
    push_build_options("");
  }
#if 0
  /** // doc: env(env const&) {{{
   * \todo Write documentation
   */ // }}}
  inline env(env const&)
  {
  }
  /** // doc: operator=(env const&) {{{
   * \todo Write documentation
   */ // }}}
  inline env&
  operator=(env const&)
  {
  }
#endif
public:
  // build options API
  /** // doc: push_build_options {{{
   * \todo Write documentation
   */ // }}}
  inline void
  push_build_options(std::string const& options, clxx::context const& context = clxx::context())
  {
    _build_options[context].push(options);
  }
  /** // doc: pop_build_options {{{
   * \todo Write documentation
   * \throws std::out_of_range
   *    If there is no build options stored for \p context
   */ // }}}
  inline void
  pop_build_options(clxx::context const& context = clxx::context())
  {
    _build_options.at(context).pop();
    if(_build_options.at(context).empty())
      _build_options.erase(context);
  }
  /** // doc: build_options {{{
   * \todo Write documentation
   * \throws std::out_of_range
   *    If there is no build options stored for \p context
   */ // }}}
  inline std::string const&
  build_options(clxx::context const& context = clxx::context()) const
  {
    // assert(!build_options.at(context).empty());
    return _build_options.at(context).top();
  }
  /** // doc: build_options {{{
   * \todo Write documentation
   * \throws std::out_of_range
   *    If there is no build options stored for \p context
   */ // }}}
  inline std::string&
  build_options(clxx::context const& context = clxx::context())
  {
    // assert(!build_options.at(context).empty());
    return _build_options.at(context).top();
  }
  /** // doc: has_build_options {{{
   * \todo Write documentation
   * \throws std::out_of_range
   *    If there is no build options stored for \p context
   */ // }}}
  inline bool
  has_build_options(clxx::context const& context = clxx::context()) const
  {
    return (this->_build_options.count(context) != 0);
  }
public:
  /** // doc: root() {{{
   * \todo Write documentation
   */ //}}}
  static env& root()
  {
    // this initialization shall be thread safe in c++11,
    // see §6.7 [stmt.dcl] p4
    static env obj;
    return obj;
  }
private:
  programs_map_t _programs;
  build_options_map_t _build_options;
};
} } // end namespace numbo::opencl

#endif /* NUMBO_OPENCL_ENV_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
