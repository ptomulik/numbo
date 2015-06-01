/*
 * @COPYRIGHT@
 * Licensed under MIT license (LICENSE.txt).
 */

// numbo/detail/ppfun_1d_nu.hpp

/** // doc: numbo/detail/ppfun_1d_nu.hpp {{{
 * \file numbo/detail/ppfun_1d_nu.hpp
 * \todo Write documentation
 */ // }}}
#ifndef NUMBO_DETAIL_PPFUN_1D_NU_HPP_INCLUDED
#define NUMBO_DETAIL_PPFUN_1D_NU_HPP_INCLUDED

#include <iterator>

namespace Numbo { namespace Detail {
/** \ingroup NumboPPFun_1d_nu
 * @{ */
/** // doc: ppfun_1d_nu_ppform_eval() {{{
 * \brief Evaluate *j*-th derivative of pp function 
 *
 * This function returns value of *j*-th derivative \f$ D^j f(x),\; j \ge 0 \f$
 * of some pp function \f$f\f$ at point \f$x = \xi_i + h\f$. The breakpoint
 * \f$\xi_i\f$ is known only to the caller and it is such that
 * \f$\xi_i \le x < \xi_{i+1}\f$ (this implies \f$0 \le h < \xi_{i+1} - \xi_i\f$).
 * The original ppform is defined by matrix of derivatives
 * \f$ \mathbf{C} = (C_{j,i}) = D^j f(\xi_i^{+}),\; j = 0,\dots,k-1,\;\;
 * i = 0, \dots, l > 0\f$. This function uses only the *i*-th column of the
 * matrix \f$\mathbf{C}\f$, that is it assumes that <tt>c[m] = \f$C_{m,i},\;\;
 * m = 0, \dots, k-1\f$</tt>.
 *
 * The function returns the evaluated derivative computed as the following sum
 * \f[ D^j f(x) = \sum_{m=1}^{k-1} \mathtt{c[m]} \cdot \mathtt{h}^{m-j}/(m-j)!.\f]
 * Internally it uses the same recursive formula as the de Boor's function 
 * <a href="http://pages.cs.wisc.edu/~deboor/pgs/ppvalu.f">ppvalu()</a> [1].
 *
 * \param[in] k
 *    order of the piecewise polynomial used to represent the pp function;
 *    it must be *k* > 0,
 * \param[in] j
 *    order of the derivative to be evaluated; it must hold *j >= 0*;
 *    for *j* = 0 the function value is evaluated; *j* >= k yields zero,
 * \param[in] c
 *    random access iterator pointing to the beginning of the *i*-th row of
 *    coefficient matrix \f$\mathbf{C} = (C_{ji}) := D^{j-1}f(\xi_i^{+})\f$
 *    (the ppform of \f$f\f$); it is assumed that <tt>c[m] = \f$C_{m,i},\;\;
 *    m = 0, \dots, k-1\f$</tt>,
 * \param[in] h
 *    coordinate of the point at which the derivative (or value) has to be
 *    evaluated; it's assumed that \f$0 \le h < \xi_{i+1} - \xi_i\f$, for some
 *    \f$i\f$ and a strictly increasing breakpoint sequence \f$\mathbf{\xi}
 *    = (\xi_i)\f$.
 *
 * \returns
 *    the value of *j*-th derivative \f$D^j f(\xi_i + h)\f$
 *
 * \b References
 *
 * 1. de Boor, Carl. A practical Guide to Splines. Springer 2001. ISBN
 *    0-387-95366-3.
 */ // }}}
template<typename CIter, typename T>
typename std::iterator_traits<CIter>::value_type
ppfun_1d_nu_ppform_eval(int k, int j, CIter c, T h) 
{
  typedef typename std::iterator_traits<CIter>::value_type C;
  C v = (C)0;
  int m, d = k - j;
  for(m = k - 1; m >= j; --m, --d)
    v = (v/d)*h + c[m];
  return v;
}
/** @} */
} } // end namespace Numbo::Detail

#endif /* NUMBO_DETAIL_PPFUN_1D_NU_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
