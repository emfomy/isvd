////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/lapack/auxiliary.h
/// \brief      The LAPACK auxiliary header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _ISVD_LA_LAPACK_AUXILARY_H_
#define _ISVD_LA_LAPACK_AUXILARY_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

@ISVD_LA_BLAS_TYPE_DEFINE@

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

extern void slarnv_(const INT *idist, INT *iseed, const INT *n, REAL4 *x);
extern void dlarnv_(const INT *idist, INT *iseed, const INT *n, REAL8 *x);
extern void clarnv_(const INT *idist, INT *iseed, const INT *n, COMP4 *x);
extern void zlarnv_(const INT *idist, INT *iseed, const INT *n, COMP8 *x);

#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_aux_module
/// \brief  Returns a vector of random numbers from a uniform or normal distribution.
//\{
static inline void isvd_sLarnv(
    const INT idist, INT *iseed, const INT n, REAL4 *x
) { slarnv_(&idist, iseed, &n, x); }
static inline void isvd_dLarnv(
    const INT idist, INT *iseed, const INT n, REAL8 *x
) { dlarnv_(&idist, iseed, &n, x); }
static inline void isvd_cLarnv(
    const INT idist, INT *iseed, const INT n, COMP4 *x
) { clarnv_(&idist, iseed, &n, x); }
static inline void isvd_zLarnv(
    const INT idist, INT *iseed, const INT n, COMP8 *x
) { zlarnv_(&idist, iseed, &n, x); }
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_aux_module
/// \brief  Tests two characters for equality regardless of the case.
bool isvd_Lsame( const CHAR1 ca, const CHAR1 cb );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_aux_module
/// \brief  Tests two character strings for equality regardless of the case.
bool isvd_Lsamen( const INT n, const CHAR1 *sa, const CHAR1 *sb );

@ISVD_LA_BLAS_TYPE_UNDEF@

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_LA_LAPACK_AUXILARY_H_
