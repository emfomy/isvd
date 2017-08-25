////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/la/lapack/larnv.h
/// @brief   The LAPACK LARNV header.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_LA_LAPACK_LARNV_H_
#define _ISVD_LA_LAPACK_LARNV_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#define CHAR1 char
#define INT   isvd_int_t
#define REAL4 float
#define REAL8 double
#define COMP4 float complex
#define COMP8 double complex

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

#if !defined(ISVD_USE_MKL)

extern void slarnv_(ISVD_UNKNOWN);
extern void dlarnv_(ISVD_UNKNOWN);
extern void clarnv_(ISVD_UNKNOWN);
extern void zlarnv_(ISVD_UNKNOWN);

#endif  // ISVD_USE_MKL

#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_lapack_module
/// Returns a vector of random numbers from a uniform or normal distribution.
//@{
static inline void isvd_slarnv(
    const INT idist, INT *iseed, const INT n, REAL4 *x
) { slarnv_(&idist, iseed, &n, x); }
static inline void isvd_dlarnv(
    const INT idist, INT *iseed, const INT n, REAL8 *x
) { dlarnv_(&idist, iseed, &n, x); }
static inline void isvd_clarnv(
    const INT idist, INT *iseed, const INT n, COMP4 *x
) { clarnv_(&idist, iseed, &n, x); }
static inline void isvd_zlarnv(
    const INT idist, INT *iseed, const INT n, COMP8 *x
) { zlarnv_(&idist, iseed, &n, x); }
//@}

#undef CHAR1
#undef INT
#undef REAL4
#undef REAL8
#undef COMP4
#undef COMP8

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_LA_LAPACK_LARNV_H_
