////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/la/vsl/rng_gaussian.h
/// \brief      The VSL RNGGAUSSIAN routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _LIBISVD_LA_VSL_RNG_GAUSSION_H_
#define _LIBISVD_LA_VSL_RNG_GAUSSION_H_

#include <libisvd/def.h>
#include <libisvd/la/vsl/vsl.h>
#include <libisvd/la/lapack/larnv.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#define CHAR1 char
#define INT   isvd_int_t
#define REAL4 float
#define REAL8 double
#define COMP4 complex float
#define COMP8 complex double

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  src_la_vsl_module
/// Creates and initializes a random stream.
//\{
#if defined(ISVD_USE_MKL)
static inline void isvd_vsRngGaussian(
    isvd_VSLStreamStatePtr stream, const INT n, REAL4 *r, const REAL4 a, const REAL4 sigma
) { isvd_assert_pass(vsRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER, stream, n, r, a, sigma)); }
static inline void isvd_vdRngGaussian(
    isvd_VSLStreamStatePtr stream, const INT n, REAL8 *r, const REAL8 a, const REAL8 sigma
) { isvd_assert_pass(vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER, stream, n, r, a, sigma)); }
#else  // ISVD_USE_MKL
static inline void isvd_vsRngGaussian(
    isvd_VSLStreamStatePtr stream, const INT n, REAL4 *r, const REAL4 a, const REAL4 sigma
) {
  isvd_sLarnv(3, stream, n, r);
  for ( INT i = 0; i < n; ++i ) r[i] = sigma * r[i] + a;
}
static inline void isvd_vdRngGaussian(
    isvd_VSLStreamStatePtr stream, const INT n, REAL8 *r, const REAL8 a, const REAL8 sigma
) {
  isvd_dLarnv(3, stream, n, r);
  for ( INT i = 0; i < n; ++i ) r[i] = sigma * r[i] + a;
}
#endif  // ISVD_USE_MKL
//\}

#undef CHAR1
#undef INT
#undef REAL4
#undef REAL8
#undef COMP4
#undef COMP8

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _LIBISVD_LA_VSL_RNG_GAUSSION_H_
