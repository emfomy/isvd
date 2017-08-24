////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/la/vsl/rng_gaussian.h
/// @brief   The VSL RNGGAUSSIAN routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_LA_VSL_RNG_GAUSSION_H_
#define _ISVD_LA_VSL_RNG_GAUSSION_H_

#include <isvd/def.h>
#include <isvd/la/vsl/vsl.h>

#define CHAR1 char
#define INT   isvd_int_t
#define REAL4 float
#define REAL8 double
#define COMP4 float complex
#define COMP8 double complex

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_vsl_module
/// Creates and initializes a random stream.
//@{
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
  isvd_slarnv(3, stream, n, r);
  for ( INT i = 0; i < n; ++i ) r[i] = sigma * r[i] + a;
}
static inline void isvd_vdRngGaussian(
    isvd_VSLStreamStatePtr stream, const INT n, REAL8 *r, const REAL8 a, const REAL8 sigma
) {
  isvd_dlarnv(3, stream, n, r);
  for ( INT i = 0; i < n; ++i ) r[i] = sigma * r[i] + a;
}
#endif  // ISVD_USE_MKL
//@}

#undef CHAR1
#undef INT
#undef REAL4
#undef REAL8
#undef COMP4
#undef COMP8

#endif  // _ISVD_LA_VSL_RNG_GAUSSION_H_