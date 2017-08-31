////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/blas/blas1.h
/// \brief      The BLAS level 1 header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _ISVD_LA_BLAS_BLAS1_H_
#define _ISVD_LA_BLAS_BLAS1_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

@ISVD_LA_BLAS_TYPE_DEFINE@

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

extern REAL4 sdot_(ISVD_UNKNOWN);
extern REAL8 ddot_(ISVD_UNKNOWN);
extern COMP4 cdotc_(ISVD_UNKNOWN);
extern COMP8 zdotc_(ISVD_UNKNOWN);
extern COMP4 cdotu_(ISVD_UNKNOWN);
extern COMP8 zdotu_(ISVD_UNKNOWN);

extern REAL4 snrm2_(ISVD_UNKNOWN);
extern REAL8 dnrm2_(ISVD_UNKNOWN);
extern REAL4 scnrm2_(ISVD_UNKNOWN);
extern REAL8 dznrm2_(ISVD_UNKNOWN);

extern REAL4 sasum_(ISVD_UNKNOWN);
extern REAL8 dasum_(ISVD_UNKNOWN);
extern REAL4 scasum_(ISVD_UNKNOWN);
extern REAL8 dzasum_(ISVD_UNKNOWN);

extern void sscal_(ISVD_UNKNOWN);
extern void dscal_(ISVD_UNKNOWN);
extern void cscal_(ISVD_UNKNOWN);
extern void zscal_(ISVD_UNKNOWN);
extern void csscal_(ISVD_UNKNOWN);
extern void zdscal_(ISVD_UNKNOWN);

#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_module
/// Computes a vector-vector dot product.
//\{
static inline REAL4 isvd_sDot(
    const INT n, const REAL4 *x, const INT incx, REAL4 *y, const INT incy
) { return sdot_(&n, x, &incx, y, &incy); }
static inline REAL8 isvd_dDot(
    const INT n, const REAL8 *x, const INT incx, REAL8 *y, const INT incy
) { return ddot_(&n, x, &incx, y, &incy); }
static inline COMP4 isvd_cDotc(
    const INT n, const COMP4 *x, const INT incx, COMP4 *y, const INT incy
) { return cdotc_(&n, x, &incx, y, &incy); }
static inline COMP8 isvd_zDotc(
    const INT n, const COMP8 *x, const INT incx, COMP8 *y, const INT incy
) { return zdotc_(&n, x, &incx, y, &incy); }
static inline COMP4 isvd_cDotu(
    const INT n, const COMP4 *x, const INT incx, COMP4 *y, const INT incy
) { return cdotu_(&n, x, &incx, y, &incy); }
static inline COMP8 isvd_zDotu(
    const INT n, const COMP8 *x, const INT incx, COMP8 *y, const INT incy
) { return zdotu_(&n, x, &incx, y, &incy); }
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_module
/// Computes the Euclidean norm of a vector.
//\{
static inline REAL4 isvd_sNrm2(
    const INT n, const REAL4 *x, const INT incx
) { return snrm2_(&n, x, &incx); }
static inline REAL8 isvd_dNrm2(
    const INT n, const REAL8 *x, const INT incx
) { return dnrm2_(&n, x, &incx); }
static inline REAL4 isvd_scNrm2(
    const INT n, const COMP4 *x, const INT incx
) { return scnrm2_(&n, x, &incx); }
static inline REAL8 isvd_dzNrm2(
    const INT n, const COMP8 *x, const INT incx
) { return dznrm2_(&n, x, &incx); }
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_module
/// Computes the sum of magnitudes of the vector elements.
//\{
static inline REAL4 isvd_sAsum(
    const INT n, const REAL4 *x, const INT incx
) { return  sasum_(&n, x, &incx); }
static inline REAL8 isvd_dAsum(
    const INT n, const REAL8 *x, const INT incx
) { return  dasum_(&n, x, &incx); }
static inline REAL4 isvd_scAsum(
    const INT n, const COMP4 *x, const INT incx
) { return scasum_(&n, x, &incx); }
static inline REAL8 isvd_dzAsum(
    const INT n, const COMP8 *x, const INT incx
) { return dzasum_(&n, x, &incx); }
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_module
/// Computes the product of a vector by a scalar.
//\{
static inline void isvd_sScal(
    const INT n, const REAL4 alpha, REAL4 *x, const INT incx
) { sscal_(&n, &alpha, x, &incx); }
static inline void isvd_dScal(
    const INT n, const REAL8 alpha, REAL8 *x, const INT incx
) { dscal_(&n, &alpha, x, &incx); }
static inline void isvd_cScal(
    const INT n, const COMP4 alpha, COMP4 *x, const INT incx
) { cscal_(&n, &alpha, x, &incx); }
static inline void isvd_zScal(
    const INT n, const COMP8 alpha, COMP8 *x, const INT incx
) { zscal_(&n, &alpha, x, &incx); }
static inline void isvd_csScal(
    const INT n, const REAL4 alpha, COMP4 *x, const INT incx
) { csscal_(&n, &alpha, x, &incx); }
static inline void isvd_zdScal(
    const INT n, const REAL8 alpha, COMP8 *x, const INT incx
) { zdscal_(&n, &alpha, x, &incx); }
//\}

@ISVD_LA_BLAS_TYPE_UNDEF@

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_LA_BLAS_BLAS1_H_
