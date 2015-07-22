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

#include <clxx/cl/program.hpp>
#include <clxx/cl/context.hpp>
#include <map>
#include <string>

namespace numbo { namespace opencl {
/** // doc: program_generator {{{
 * \brief Program generator
 *
 * This is a base class for OpenCL program generators. An OpenCL program
 * generator generates program source, builds it for a given context
 * and memoizes the corresponding \c clxx::program object in an internal 
 * context-program map. The class follows lazy creation concept. A program is
 * generated/built only once for a given context and then gets memoized. Each
 * subsequent call to the #get_program() method retrieves and returns the memoized
 * \c clxx::program object.
 *
 * The template shall be used as a base class in
 * <a href="https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern">CRTP</a>
 * pattern.
 *
 * The derived class must implement the following methods:
 * - <tt>void generate_source(clxx::program_source&) const</tt>,
 * - <tt>std::string program_name() const</tt>.
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
 *    void generate_source(clxx::program_source& src)
 *    { src.append("__kernel void trivial() { }\n"); }
 *    std::string program_name() const
 *    { return "trivial"; }
 *    using program_generator<trivial>::get_program;
 *  };
 * \endcode
 *
 * Retrieving the program:
 *
 * \code
 * clxx::context context(...);
 * // ...
 * clxx::program program( trivial::get_program(context) );
 * \endcode
 *
 * \todo Elaborate a way to configure generators 
 * \todo Implement build options in #get_program()
 */ // }}}
class program_generator
{
private:
  mutable std::map<clxx::context, clxx::program> _programs;
  // Prevent instance creation and copying...
  //program_generator() = delete;
  program_generator(program_generator const&) = delete;
  void operator=(program_generator const&) = delete;
protected:
  /** // doc: generate(context)  {{{
   * \brief For internal use. Generates the program for given context
   */ // }}}
  clxx::program
  generate(clxx::context const& context) const
  {
    clxx::program_source src;
    this->generate_source(src);
    return clxx::program(context, clxx::program_sources{src});
  }
public:
  /** // doc: program_generator() {{{
   * \todo Write documentation
   */ // }}}
  program_generator() = default;
  /** // doc: ~program_generator() {{{
   * \todo Write documentation
   */ // }}}
  virtual ~program_generator() {}
  /** // doc: generate_source() {{{
   * \todo Write documentation
   */ // }}}
  virtual void generate_source(clxx::program_source& src) const = 0;
  /** // doc: program_name() {{{
   * \todo Write documentation
   */ // }}}
  virtual std::string program_name() const = 0;
  /** // doc: program_dirname() {{{
   * \todo Write documentation
   */ // }}}
  virtual std::string program_dirname() const
  { return "numbo"; }
  /** // doc: program_path() {{{
   * \todo Write documentation
   */ // }}}
  virtual std::string
  program_path() const
  { return program_dirname() + "/" + program_name() + ".cl"; }
  /** // doc: generate_line_directive() {{{
   * \brief Appends '#line' preprocessing directive to src
   * \todo Write documentation
   */ // }}}
  virtual void
  generate_line_directive(clxx::program_source& src, size_t line) const
  {
    src.append("#line ");
    src.append(std::to_string(line));
    src.append(" \"");
    src.append(program_path());
    src.append("\"\n");
  }
  /** // doc: get_program(context,force_generate) {{{
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
   *
   * \todo This function is not thread safe, but it should be. Revisit it.
   */ // }}}
  clxx::program
  get_program(clxx::context const& context, bool force_generate = false) const
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
  size_t erase(clxx::context const& context) const
  { return _programs.erase(context); }
  /** // doc: clear() {{{
   * \brief Forget all memoized program instances
   */ // }}}
  void clear() const
  { _programs.clear(); }
};
} } // end namespace numbo::opencl

#endif /* NUMBO_OPENCL_PROGRAM_GENERATOR_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
