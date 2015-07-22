/*
 * @COPYRIGHT@
 * Licensed under MIT license (LICENSE.txt).
 */

// numbo/opencl/programs/ppfun_1d_nu.hpp

/** // doc: numbo/opencl/programs/ppfun_1d_nu.hpp {{{
 * \file numbo/opencl/programs/ppfun_1d_nu.hpp
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_OPENCL_PROGRAMS_PPFUN_1D_NU_HPP_INCLUDED
#define NUMBO_OPENCL_PROGRAMS_PPFUN_1D_NU_HPP_INCLUDED

#include <numbo/opencl/util/type_to_string.hpp>
#include <numbo/opencl/program_generator.hpp>


namespace numbo { namespace opencl { namespace programs {
template<typename NumericT>
class ppfun_1d_nu
  : program_generator< ppfun_1d_nu<NumericT> >
{
public:
  typedef program_generator< ppfun_1d_nu<NumericT> > base_type;
  using base_type::get;

  static constexpr size_t program_source_estimated_size = 1ul;
  using NumericToS = util::type_to_string<NumericT, util::floating_type_tag>;

  static void generate_program_source(clxx::program_source& src)
  {
    // nothing here yet...
  }
};

} } } // end namespace numbo::opencl::programs

#endif /* NUMBO_OPENCL_PROGRAMS_PPFUN_1D_NU_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
