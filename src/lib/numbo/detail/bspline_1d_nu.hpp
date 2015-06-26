/*
 * @COPYRIGHT@
 * Licensed under MIT license (LICENSE.txt).
 */

// numbo/detail/bspline_1d_nu.hpp

/** // doc: numbo/detail/bspline_1d_nu.hpp {{{
 * \file numbo/detail/bspline_1d_nu.hpp
 * \brief Funcions implementing 1-dimensional single-valued non-uniform B-splines
 */ // }}}
#ifndef NUMBO_DETAIL_BSPLINE_1D_NU_HPP_INCLUDED
#define NUMBO_DETAIL_BSPLINE_1D_NU_HPP_INCLUDED

#include <iterator>
#include <cstddef>
#include <cmath>

namespace numbo { namespace detail  {
/** \ingroup NumboBsplines_1d_nu
 * @{ */
/** // doc: bspline_1d_nu_deltas() {{{
 * \brief Prepare certain differences \f$\Delta_s\f$ for use in
 * bspline_1d_nu_values()
 *
 * This function computes differences \f$\Delta_s(x)\f$ for further use in
 * bspline_1d_nu_bvalues(). The computed differences are defined as
 *
 *
 * \f[
 *  \Delta_s(x) = x - t_{i-(k-1)+s},\;\;\;
 *  s = 1, \dots, 2 \cdot (k - 1),\;\;\;
 *  k \ge 1
 * \f]
 *
 * The corresponding values of \f$\delta^L_s\f$ and \f$\delta^R_s\f$ that
 * should be passed to bspline_1d_nu_raise() are then
 * \f[
 *  \delta^L_s = \Delta_{s+(k-1)-j},\;\;\;
 *  \delta^R_s = \Delta_{s+(k-1)},\;\;\;
 *  s = 1, \dots, j, \;\;\; 1 \le j < k
 * \f]
 *
 * When invoking \ref bspline_1d_nu_raise() use
 *    - <tt>dl = dk+(k-1)-j</tt>, and
 *    - <tt>dr = dk+(k-1)</tt>,
 *
 * that is 
 * \code
 *    bspline_1d_nu_raise(j,dk+(k-1)-j,dk+(k-1),...)
 * \endcode
 * for <tt>1 <= j < k</tt>.
 *
 * \param[in] k
 *    the (maximal) order of splines being considered, must be <tt>k > 0</tt>,
 *    calling the function with k = 0 results with an undefined behavior,
 *
 * \param[in] ti
 *    random access iterator pointing to the nearest knot of the B-spline to
 *    the left of point *x*; the range of iterators
 *    <tt>[ti - k + 2, ti + k)</tt> must be a valid range in the knot
 *    sequence; in most circumstances <tt>ti</tt> shall be chosen such that
 *      - <tt>ti[0] < ti[1]</tt>, and
 *      - <tt>ti[0] <= x <= ti[1]</tt>,
 *
 * \param[in] x
 *    independent coordinate at which the differences are being computed,
 *
 * \param[out] dk
 *    mutable random access iterator pointing to the beginning of a sequence
 *    able to store at least <tt>2*(k-1)</tt> elements; the computed values of
 *    \f$\Delta_s\f$ get stored in this sequence as follows
 *      - <tt>dk[0] = \f$\Delta_1\f$</tt>,
 *      - <tt>...</tt>,
 *      - <tt>dk[2*(k-1)-1] = \f$\Delta_{2*(k-1)}\f$</tt>,
 *
 * \b Example
 *
 * \snippet numbo/bspline_1d_nu_bvalues1.cpp Main
 *
 * \b Output
 *
 * \snippet numbo/bspline_1d_nu_bvalues1.cpp Output
 *
 */ // }}}
template<typename KnotIter, typename T, typename DIter>
void bspline_1d_nu_deltas(size_t k, KnotIter ti, T x, DIter dk)
{
  size_t s_1;             /*  s_1 stands for (s-1) */
  size_t _2k_1 = 2*(k-1); /* _2k_1 stands for 2*(k-1) */
  for(s_1 = 0; s_1 < _2k_1; ++s_1)  // s = 1 .. 2*(k-1)
    {
      dk[s_1] = x - ti[s_1 + 2 - k];
    }
}
/** // doc: bspline_1d_nu_raise() {{{
 * \brief Raise order of B-spline base functions
 *
 * In short, the function computes values of B-spline base functions
 * \f$B_{s,j+1}(x)\f$ of order *j*+1 at some point *x* based on values
 * \f$B_{s,j}(x)\f$ of base functions of order *j* at the same point *x* and
 * for the same knot sequence. The point *x* is not provided explicitly to the
 * function, but via series of differences \f$\delta^L_s\f$, \f$\delta^R_s\f$
 * defined below.
 *
 * In detail, given a series of base function values
 * \f$b_r := B_{i-j+r,j}(x),\;\;r=1,\dots,j\f$ of order \f$j\f$ evaluated
 * at \f$x\f$ and series of differences
 *
 * \f[
 *  \delta^L_s = x - t_{i-j+s}, \;\;
 *  \delta^R_s = x - t_{i+s}, \;\;
 *  s = 1, \dots, j
 * \f]
 *
 * where \f$t_j\f$ are B-spline knots, \f$i\f$ is chosen such that \f$t_i <
 * t_{i+1}\f$ and \f$t_i \le x \le t_{i+1}\f$, the function determines new
 * values of base functions \f$(b^{'})_r := B_{i-j+r-1,j+1}(x),\;\; r=1,\dots,j+1\f$
 * of order \f$j+1.\f$ The new base functions are determined by the formula
 * \f[
 *  (b^{'})_r := B_{i-j+r-1,j+1} =
 *    \delta^L_{r-1} \frac{b_{r-1}}{\delta^L_{r-1}-\delta^R_{r-1}}
 *  - \delta^R_{r} \frac{b_{r}}{\delta^L_{r}-\delta^R_r}, \;\;\;
 *  r = 1, \dots, j+1
 * \f]
 * The formula is based on the formula X(2) from [1], and differs only in
 * definition of \f$\delta^L_s\f$ (we use differend indexing) and
 * \f$\delta^R_s\f$ (we've changed the sign). That way, we have
 * \f$\delta^R_{s}=\delta^L_{s+j}\f$.
 *
 * The function assumes \f$b_0 := B_{i-j,j} = 0\f$, \f$b_{j+1} := B_{i+1,j} =
 * 0\f$. The elements \f$\delta^L_0\f$, \f$\delta^L_{j+1}\f$,
 * \f$\delta^R_0\f$, \f$\delta^R_{j+1}\f$ are never accessed.
 *
 * \param[in] j
 *    the order of the base function values stored in *bi* on input,
 * \param[in] dl
 *    random access iterator pointing to the beginning of sequence of at
 *    least *j* elements (differences \f$\delta^L_s\f$), such that:
 *      - <tt>dl[0]==\f$\delta^L_1\f$</tt>,
 *      - <tt>...</tt>,
 *      - <tt>dl[j-1]==\f$\delta^L_j\f$</tt>,
 *
 * \param[in] dr
 *    random access iterator pointing to the beginning of sequence of at
 *    least *j* elements (differences \f$\delta^R_s\f$), such that:
 *      - <tt>dr[0]==\f$\delta^R_1\f$</tt>,
 *      - <tt>...</tt>,
 *      - <tt>dr[j-1]==\f$\delta^R_j\f$</tt>,
 *
 * \param[in] bi
 *    random access iterator pointing to the beginning of sequence of at
 *    least *j* elements (base functions \f$B_{s,j}\f$), such that:
 *      - <tt>bi[0] == \f$b_1 := B_{i-j+1,j}(x)\f$</tt>,
 *      - <tt>...</tt>,
 *      - <tt>bi[j-1] == \f$b_j := B_{i,j}(x)\f$</tt>,
 *
 * \param[out] bo
 *    mutable random access iterator pointing to the beginning of sequence used
 *    to store the *j+1* computed base functions \f$B_{s,j+1}\f$, such that:
 *      - <tt>bo[0] = \f$(b^{'})_1 = B_{i-j,j+1}(x)\f$</tt>,
 *      - <tt>...</tt>,
 *      - <tt>bo[j] = \f$(b^{'})_{j+1} = B_{i,j+1}(x)\f$</tt>
 *
 * It's acceptable to provide *bi* and *bo* traversing over the same sequence,
 * in which case the function will compute new values of base functions in
 * place.
 *
 * \b References
 *
 * 1. de Boor, Carl. A practical Guide to Splines. Springer 2001. ISBN
 *    0-387-95366-3.
 */ // }}}
template<typename DlIter, typename DrIter, typename BiIter, typename BoIter>
void bspline_1d_nu_raise(size_t j, DlIter dl, DrIter dr, BiIter bi, BoIter bo)
{
  typedef typename std::iterator_traits<BoIter>::value_type BoT;
  BoT saved, term;
  size_t r_1; /* r_1 stands for (r - 1) */

  saved = (BoT)0;
  for(r_1 = 0; r_1 < j; ++r_1) // r = 1 .. j
  {
    term = bi[r_1]/(dl[r_1] - dr[r_1]);
    bo[r_1] = saved - dr[r_1]*term;
    saved = dl[r_1]*term;
  }
  bo[r_1] = saved;
}
/** // doc: bspline_1d_nu_raise_w_stride() {{{
 * \brief Raise order of B-spline base functions
 *
 * Merely, it's same as bspline_1d_nu_raise(). The difference is in how
 * it reads values from *bi* and stores the result in *bo*. For
 * <tt>r = 0, 1, .., j-1</tt> the function reads values from
 * <tt>bi[r * stride]</tt> and writes resultant values to
 * <tt>bo[r * stride]</tt>.
 *
 * \param[in] j
 *    the order of the base function values stored in *bi* on input,
 * \param[in] dl
 *    random access iterator pointing to the beginning of sequence of at
 *    least *j* elements (differences \f$\delta^L_s\f$), such that:
 *      - <tt>dl[0]==\f$\delta^L_1\f$</tt>,
 *      - <tt>...</tt>,
 *      - <tt>dl[j-1]==\f$\delta^L_j\f$</tt>,
 *
 * \param[in] dr
 *    random access iterator pointing to the beginning of sequence of at
 *    least *j* elements (differences \f$\delta^R_s\f$), such that:
 *      - <tt>dr[0]==\f$\delta^R_1\f$</tt>,
 *      - <tt>...</tt>,
 *      - <tt>dr[j-1]==\f$\delta^R_j\f$</tt>,
 *
 * \param[in] stride
 *    distance between two indices in *bi* (or *bo*) containing consecutive
 *    B-spline values,
 *
 * \param[in] bi
 *    random access iterator pointing to the beginning of sequence of at
 *    least *j* elements (base functions \f$B_{s,j}\f$), such that:
 *      - <tt>bi[0*stride] == \f$b_1 := B_{i-j+1,j}(x)\f$</tt>,
 *      - <tt>bi[1*stride] == \f$b_1 := B_{i-j+2,j}(x)\f$</tt>,
 *      - <tt>...</tt>,
 *      - <tt>bi[(j-1)*stride] == \f$b_j := B_{i,j}(x)\f$</tt>,
 *
 * \param[out] bo
 *    mutable random access iterator pointing to the beginning of sequence used
 *    to store the *j+1* computed base functions \f$B_{s,j+1}\f$, such that:
 *      - <tt>bo[0*stride] = \f$(b^{'})_1 = B_{i-j,j+1}(x)\f$</tt>,
 *      - <tt>bo[1*stride] = \f$(b^{'})_1 = B_{i-j+1,j+1}(x)\f$</tt>,
 *      - <tt>...</tt>,
 *      - <tt>bo[j*stride] = \f$(b^{'})_{j+1} = B_{i,j+1}(x)\f$</tt>
 *
 * It's acceptable to provide *bi* and *bo* traversing over the same sequence,
 * in which case the function will compute new values of base functions in
 * place.
 *
 * \b References
 *
 * 1. de Boor, Carl. A practical Guide to Splines. Springer 2001. ISBN
 *    0-387-95366-3.
 */ // }}}
template<typename DlIter, typename DrIter, typename BiIter, typename BoIter>
void bspline_1d_nu_raise_w_stride(size_t j, DlIter dl, DrIter dr,
                                  ptrdiff_t stride, BiIter bi, BoIter bo)
{
  typedef typename std::iterator_traits<BoIter>::value_type BoT;
  BoT saved, term;
  size_t r_1; /* r_1 stands for (r - 1) */

  saved = (BoT)0;
  for(r_1 = 0; r_1 < j; ++r_1) /* r = 1 .. j */
  {
    term = bi[r_1 * stride]/(dl[r_1] - dr[r_1]);
    bo[r_1 * stride] = saved - dr[r_1]*term;
    saved = dl[r_1]*term;
  }
  bo[r_1*stride] = saved;
}
/** // doc: bspline_1d_nu_bvalues() {{{
 * \brief Determine values of B-spline base functions of given order
 *
 * This function determines \f$k_o\f$ values of base functions
 * \f$B_{i-k_o+1,k_o}(x)\f$, ..., \f$B_{i,k_o}(x)\f$ of order \f$k_o\f$ and
 * stores the result in sequence *b*. The value of *x* is not given explicitly
 * but via *dkl* and *dkr* computed with \ref bspline_1d_nu_deltas()
 * "bspline_1d_nu_deltas(k,t,i,x,dkl,dkr)". The index *i* is such
 * that \f$t_i < t_{i+1}\f$ and \f$t_i \le x \le t_{i+1}\f$. If *ki* > 0, then
 * it's assumed than sequence *b* initially contains *ki* values of
 * B-functions \f$B_{i-k_i+1,k_i}(x)\f$, ..., \f$B_{i,k_i}\f$ or order
 * \f$k_i\f$. The new values of order \f$k_o\f$ will be computed in-place.
 *
 * \param[in] k
 *    maximum possible order of the B-spline functions; this determines the
 *    size of sequences *dkl* and *dkr* (each should be of size k-1);
 *    it must also hold *ki* <= *ko* <= *k*, this condition is not verified
 *    anywhere within the function,
 * \param[in] dk
 *    random access iterator to the sequence of differences
 *    <tt>dk[s-1] = \f$\Delta_s\f$</tt>, \f$s = 1, \dots, k-1\f$,
 *    determined with bspline_1d_nu_deltas()
 * \param[in] ki
 *    the order of B-spline base function values stored in *b* at input;
 *    it's required than *ki* <= *ko*
 * \param[in] ko
 *    the order of B-spline base function values stored in *b* at output;
 *    it's required than *ki* <= *ko*
 * \param[inout] b
 *    at input, sequence of values of B-spline base functions of order *ki*;
 *    at output, new sequence of values of B-spline base functions of order *ko*;
 *    with this, we have <tt>b[r-1] == \f$B_{i-k_i+r,k_i}\f$</tt>,
 *    <tt>r=1, .., ki</tt> at input, and <tt>b[r-1] == \f$B_{i-k_o+r,k_o}\f$</tt>,
 *    <tt>r=1, .., ko</tt> at output.
 */ // }}}
template<typename DIter, typename BIter>
void bspline_1d_nu_bvalues(size_t k, DIter dk, size_t ki, size_t ko, BIter b)
{
  typedef typename std::iterator_traits<BIter>::value_type T;

  size_t j = ki;
  if(j == 0u && ko > 0u)
    {
      b[0] = (T)1;
      j = 1;
    }
  for(;j < ko; ++j)
  {
    bspline_1d_nu_raise(j, dk+(k-1)-j, dk+(k-1), b, b);
  }
}
/** // doc: bspline_1d_nu_bvalues_w_stride() {{{
 * \brief Determine values of B-spline base functions of given order
 *
 * Merely, its same as bspline_1d_nu_bvalues(). The difference is only in
 * how it reads and writes values to *b*. Instead of storing consecutive
 * B-spline values in adjacent elements of *b* (such that <tt>b[r] = \f$B_{i -
 * k_o + 1 + r}(x)\f$</tt>, it places them such that the storage distance
 * between two consecutive values is equal to *stride* (such that
 * <tt>b[r*stride] = \f$B_{i - k_o + 1 + r}\f$</tt>).
 * 
 * \param[in] k
 *    maximum possible order of the B-spline functions; this determines the
 *    size of sequences *dkl* and *dkr* (each should be of size k-1);
 *    it must also hold *ki* <= *ko* <= *k*, this condition is not verified
 *    anywhere within the function,
 * \param[in] dk
 *    random access iterator to the sequence of differences
 *    <tt>dk[s-1] = \f$\Delta_s\f$</tt>, \f$s = 1, \dots, k-1\f$,
 *    determined with bspline_1d_nu_deltas()
 * \param[in] ki
 *    the order of B-spline base function values stored in *b* at input;
 *    it's required than *ki* <= *ko*
 * \param[in] ko
 *    the order of B-spline base function values stored in *b* at output;
 *    it's required than *ki* <= *ko*
 * \param[in] stride
 *    index distance between two consecutive B-spline values in *b*,
 * \param[inout] b
 *    at input, sequence of values of B-spline base functions of order *ki*;
 *    at output, new sequence of values of B-spline base functions of order *ko*;
 *    with this, we have <tt>b[(r-1)*stride] == \f$B_{i-k_i+r,k_i}\f$</tt>,
 *    <tt>r=1, .., ki</tt> at input, and
 *    <tt>b[(r-1)*stride] == \f$B_{i-k_o+r,k_o}\f$</tt>, <tt>r=1, .., ko</tt>
 *    at output.
 */ // }}}
template<typename DIter, typename BIter>
void bspline_1d_nu_bvalues_w_stride(size_t k, DIter dk, size_t ki, size_t ko,
                                    ptrdiff_t stride, BIter b)
{
  typedef typename std::iterator_traits<BIter>::value_type T;

  size_t j = ki;
  if(j == 0u && ko > 0u)
    {
      b[0] = (T)1;
      j = 1;
    }
  for(;j < ko; ++j)
    {
      bspline_1d_nu_raise_w_stride(j, dk+(k-1)-j, dk+(k-1), stride, b, b);
    }
}
/** // doc: bspline_1d_nu_interp_spcol() {{{
 *
 * \brief Assembles collocation matrix for B-spline interpolation
 *
 * Given a non-decreasing sequence of \f$n+k\f$ knots
 * \f$t_j,\;\;j=0,\,\dots,n+k-1\f$ and a strictly increasing sequence of sites
 * \f$x_i,\;\;i=0,\,\dots,\,n-1\f$, the function determines all possibly
 * non-zero coefficients \f$B_{j,k}(x_i)\f$ (values of B-spline base
 * functions), and puts them into a (banded) matrix
 * \f${\bar A} := (A_{i,j})_{i,j=0}^{n-1} = (B_j(x_i))_{i,j = 0}^{n-1}\f$, 
 * called *spline collocation matrix*.
 *
 * The sites \f$x_i\f$ are assumed to be points, at which values of
 * a function \f$f\f$ (to be interpolated) are given. If \f$n >= k\f$ and knots
 * interplay well with sites (Schoenberg-Whitney theorem and the assumptions on
 * \f$x_i\f$ mentioned in documentation of the parameter *x*), then
 * the interpolation problem may be written as a problem of determining \f$n\f$
 * coefficients \f${\bar \alpha} = (\alpha_j)_{j=0}^{n-1}\f$ from the following
 * linear system
 * \f[
 *   {\bar A} {\bar \alpha} = {\bar f}
 * \f]
 * where \f${\bar f}\f$ is a vector of values \f$(f(x_i))_{i=0}^{n-1}\f$ of
 * the interpolated function \f$f\f$ at the prescribed sites \f$x_i\f$.
 * Evaluating the resultant piecewise-polynomial at "arbitrary" point
 * \f$x\f$ may then be (theoretically) performed as follows \f$\tilde{f}(x) =
 * \sum_j \alpha_j B_{j,k}(x)\f$.
 *
 * If the assumption of Schoenberg-Whitney theorem hold, then the generated
 * banded matrix (the matrix \f${\bar A}\f$) is invertible. In addition,
 * the matrix is totally-positive, which in practice means that it might be
 * LU-factorized without pivoting.
 *
 * The resultant matrix \f${\bar A}\f$ is stored in a 1-dimensional banded
 * storage *b* in a way compatible with LAPACK and several other libraries
 * that implement banded matrices. The following pictogram shows an example
 * of mapping between a \f$9 \times 9\f$ banded matrix \f${\bar A}\f$ (*k*=4,
 * *n*=5) and a 2-dimensional array \f${\bar B}\f$ (with the minimal supported
 * column length \f$m_b = 2 \cdot (k- 1) + 1 = 2 \cdot (4-1)+1 = 7\f$) used to
 * implement banded storage
 *
 * \code
 *      [ 11 12 13 14                ]
 *      [ 21 22 23 24 25             ]          [ ** ** ** 14 25 36 47 58 69 ]
 *      [ 31 32 33 34 35 36          ]          [ ** ** 13 24 35 46 57 68 79 ]
 *      [ 41 42 43 44 45 46 47       ]          [ ** 12 23 34 45 56 67 78 89 ]
 *  A = [    52 53 54 55 56 57 58    ]  --> B = [ 11 22 33 44 55 66 77 88 99 ]
 *      [       63 64 65 66 67 68 69 ]          [ 21 32 43 54 65 76 87 98 ** ]
 *      [          74 75 76 77 78 79 ]          [ 31 42 53 64 75 86 97 ** ** ]
 *      [             85 86 87 88 89 ]          [ 41 52 63 74 85 96 ** ** ** ]
 *      [                96 97 98 99 ]
 *
 *  --> b = [ ** ** ** 11 21 31 41 ** ** 12 22 32 42 52 ** 13 23 33 43 53 63 14 24 ... ]
 * \endcode
 *
 * The elements marked with stars are never referenced by the function. The
 * mapping between \f${\bar B}\f$ and the 1-dimensional storage *b* provided
 * to the function as an argument is simply <tt>\f$B(i,j)\f$ -> b[i +
 * mb*j]</tt>, where <tt>mb >= 2(k-1)+1</tt> is another parameter provided to
 * the function.
 *
 * \param[in]   k
 *    order of B-splines to be used for interpolation; it must be <tt>k>0</tt>,
 *    otherwise undefined behaviour may occur,
 * \param[in]   n
 *    number of sites \f$x_i\f$ used to construct the interpolating spline,
 *    it must be <tt>n > 0</tt>,
 * \param[in]   t
 *    random access iterator pointing to the beginning of a *non-decreasing*
 *    sequence of knots \f$t_j\f$ that define the B-splines; the size of the
 *    sequence must be at least *n+k*; the function does not examine whether
 *    the sequence is non-decreasing, if it's not, then undefined behavior may
 *    occur,
 * \param[in]   x
 *    random access iterator pointing to the beginning of a *strictly-increasing*
 *    sequence of interpolation sites \f$x_i\f$; the size of this sequence
 *    must be at least *n*; the following conditions must be met (otherwise,
 *    undefined behavior may occur):
 *      - \f$t_i \le x_i < t_{i+k}\f$, all \f$i\f$ or \f$x_{n-1} = t_{n+k-1}\f$
 *        (for \f$i = n-1\f$,
 *      - \f$t_{k-1} \le x_0\f$,
 *      - \f$x_{n-1} \le t_n\f$,
 * \param[in]   md
 *    minor dimension of the array pointed to by *d*; it's required that
 *    <tt>md >= 2*(k-1)</tt>; see below for details,
 * \param[in]   d
 *    random access iterator pointing to the beginning of a working storage
 *    used to store \f$2 \cdot (k-1) \times n\f$ values of certain differences
 *    \f$\Delta_s(x_i)\f$, the values are stored as follows:
 *      - <tt>d[md*i+(s-1)]=\f$\Delta_s(x_i):=x_i-t_{j-(k-1)+s}\f$</tt>,
 *        \f$s = 1\;..\;2\cdot(k-1)\f$, \f$i = 0\;..\;n-1\f$,
 *        \f$j:i \le j < i+k \land t_j \le x_i < t_{j+1}\f$
 * \param[in]   mb
 *    number of elements allocated for single column in the array *b*;
 *    the element <tt>B(r,c)</tt> of the banded storage is mapped to <tt>b[r +
 *    c*mb]</tt>; it's required that <tt>mb >= 2*(k-1) + 1</tt>,
 * \param[out]  b
 *    mutable random access iterator pointing to the beginning of a banded
 *    storage which is used to keep elements of the resultant banded matrix;
 *    the resultant coefficients will be written to this storage; the storage
 *    is assumed to be organized as LAPACK banded matrix storage with total of
 *    *mb* bands and *n* columns; it must hold <tt>mb >= 1 + 2*(k-1)</tt>; the
 *    total size of the storage *b* must be at least <tt>mb*n</tt> elements;
 *    the storage should be filled with zeros before calling this function.
 *
 *
 * \returns
 *    on failure, the function returns an index *i* of the first site *x[i]*
 *    which fails to satisfy assumption necessary to obtain non-singular
 *    coefficient matrix; on success the returned value is equal to *n*+1.
 * 
 * \b Example:
 *
 * \snippet bspline_1d_nu_interp_spcol1.cpp Code
 *
 * \b Output:
 *
 * \snippet bspline_1d_nu_interp_spcol1.cpp Output
 */ // }}}
template<typename TIter, typename XIter, typename DIter, typename BIter>
size_t bspline_1d_nu_interp_spcol(size_t k, size_t n, TIter t, XIter x,
                                  size_t md, DIter d, size_t mb, BIter b)
{
  using std::min;
  using std::max;
  size_t i, j;
  size_t stride = mb - 1;
  size_t jmin, jmax;
  if(n < k)
    return 0;
  /* loop over i to construct the n interpolation equations */
  for(i = 0; i < n; ++i)
    {
      /* Find j in the interval [i .. i+k) such that t[j] <= x[i] < t[j+1],
       * or t[j] < x[i] = t[j+1]. The resultant matrix is singular if it's
       * not possible */
      jmin = max(i, k-1);
      jmax = min(i+k, n);
      if(x[i] < t[jmin])
        break;
      for(j = jmin; j < jmax; ++j)
        {
          if(t[j] <= x[i] && x[i] < t[j+1])
            break;
        }
      if(j == jmax)
        {
          if(x[i] > t[j])
            break; /* not found */
          --j; /* after this, we have x[i] == t[j+1] */
        }
      bspline_1d_nu_deltas(k, t + j, x[i], d + md * i);
      bspline_1d_nu_bvalues_w_stride(k, d + md * i, 0, k, stride,
                                     b + (k-1) + i + stride*(j-(k-1)));
    }
  return i;
}
/** @} */
} } // end namespace numbo::detail

#endif /* NUMBO_DETAIL_BSPLINE_1D_NU_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
