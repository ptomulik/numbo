/*
 * @COPYRIGHT@
 * Licensed under MIT license (LICENSE.txt).
 */

// numbo/opencl/program_generator.hpp

/** // doc: numbo/opencl/program_generator.hpp {{{
 * \file numbo/opencl/program_generator.hpp
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_OPENCL_PROGRAM_GENERATOR_HPP_INCLUDED
#define NUMBO_OPENCL_PROGRAM_GENERATOR_HPP_INCLUDED

#include <numbo/opencl/env.hpp>
#include <clxx/cl/program.hpp>
#include <clxx/cl/context.hpp>
#include <map>

namespace numbo { namespace opencl {
/** // doc: program_generator {{{
 * \brief Program generator
 *
 * This is a base class for OpenCL program generators. An OpenCL program
 * generator generates program source, builds it for a given context
 * and memoizes the corresponding \c clxx::program object in an internal 
 * context-program map. The class follows lazy creation concept. A program is
 * generated/built only once for a given context and then gets memoized. Each
 * subsequent call to the #get() method retrieves and returns the memoized
 * \c clxx::program object.
 *
 * The template shall be used as a base class in
 * <a href="https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern">CRTP</a>
 * pattern.
 *
 * \tparam Derived
 *    Name of the derived class that uses program_generator base.
 * 
 * The derived class must implement static method named
 * \c generate_program_source() with the following prototype:
 *
 * \code
 *    static void generate_program_source(clxx::program_source& src);
 * \endcode
 *
 * It should write an OpenCL program source to the \c src.
 *
 * \par Example
 *
 * A trivial program with one empty kernel:
 *
 * \code
 *  class trivial
 *    : public program_generator<trivial>
 *  {
 *  public:
 *    static void generate_program_source(clxx::program_source& src)
 *    { src.append("__kernel void trivial() { }\n"); }
 *    using program_generator<trivial>::get;
 *  };
 * \endcode
 *
 * Retrieving the program:
 *
 * \code
 * clxx::context context(...);
 * // ...
 * clxx::program program( trivial::get(context) );
 * \endcode
 *
 * \todo Elaborate a way to configure generators 
 * \todo Implement build options in #get()
 */ // }}}
template<class Derived>
class program_generator
{
private:
  static std::map<clxx::context, clxx::program> _programs;
  // Prevent instance creation and copying...
  program_generator() = delete;
  program_generator(program_generator const&) = delete;
  void operator=(program_generator const&) = delete;
protected:
  /** // doc: generate(context)  {{{
   * \brief For internal use. Generates and builds the program for given context
   */ // }}}
  static clxx::program
  generate(clxx::context const& context)
  {
    clxx::program_source src;
    Derived::generate_program_source(src);
    clxx::program program(context, clxx::program_sources{src});
    clxx::build_program(program, "");
    return program;
  }
public:
  /** // doc: get(context,force_generate) {{{
   * \brief Generate and return an OpenCL program
   *
   * \param context
   *    A clxx::context object, for which the program is to be generated
   * \param force_generate
   *    Force program generation. If the program is already memoized, the
   *    memoized version is discarded and the program is generated and built
   *    again.
   *
   * \returns
   *    A program built for the given context
   */ // }}}
  static clxx::program
  get(clxx::context const& context, bool force_generate = false)
  {
    if(!force_generate)
      {
        try {
          return _programs.at(context);
        } catch(std::out_of_range const&) {
          return _programs[context] = generate(context);
        }
      }
    else
      return _programs[context] = generate(context);
  }
  /** // doc: erase(context) {{{
   * \brief Forget the memoized program instance for the \p context
   *
   * This methods removes the program memoized for given \p context from the
   * internal map. The result is that the next time the program will be
   * requested for \p context (via #get()), it will be generated and built from
   * scratch.
   *
   * \param context
   *    A \c clxx::context
   * \return
   *    The number of entries erased from the internal map, which is at most 1.
   */ // }}}
  static size_t erase(clxx::context const& context)
  { return _programs.erase(context); }
  /** // doc: clear() {{{
   * \brief Forget all memoized program instances
   */ // }}}
  static void clear()
  { _programs.clear(); }
};
} } // end namespace numbo::opencl

#endif /* NUMBO_OPENCL_PROGRAM_GENERATOR_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
