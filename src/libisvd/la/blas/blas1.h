////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/la/blas/blas1.h
/// \brief      The BLAS level 1 header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _LIBISVD_LA_BLAS_BLAS1_H_
#define _LIBISVD_LA_BLAS_BLAS1_H_

#include <libisvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#define CHAR1 char
#define INT   isvd_int_t
#define REAL4 float
#define REAL8 double
#define COMP4 complex float
#define COMP8 complex double

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
/// \ingroup  src_la_blas_module
/// Computes a vector-vector dot product.
//\{
static inline REAL4 isvd_sdot(
    const INT n, const REAL4 *x, const INT incx, REAL4 *y, const INT incy
) { return sdot_(&n, x, &incx, y, &incy); }
static inline REAL8 isvd_ddot(
    const INT n, const REAL8 *x, const INT incx, REAL8 *y, const INT incy
) { return ddot_(&n, x, &incx, y, &incy); }
static inline COMP4 isvd_cdotc(
    const INT n, const COMP4 *x, const INT incx, COMP4 *y, const INT incy
) { return cdotc_(&n, x, &incx, y, &incy); }
static inline COMP8 isvd_zdotc(
    const INT n, const COMP8 *x, const INT incx, COMP8 *y, const INT incy
) { return zdotc_(&n, x, &incx, y, &incy); }
static inline COMP4 isvd_cdotu(
    const INT n, const COMP4 *x, const INT incx, COMP4 *y, const INT incy
) { return cdotu_(&n, x, &incx, y, &incy); }
static inline COMP8 isvd_zdotu(
    const INT n, const COMP8 *x, const INT incx, COMP8 *y, const INT incy
) { return zdotu_(&n, x, &incx, y, &incy); }
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  src_la_blas_module
/// Computes the Euclidean norm of a vector.
//\{
static inline REAL4 isvd_snrm2(
    const INT n, const REAL4 *x, const INT incx
) { return snrm2_(&n, x, &incx); }
static inline REAL8 isvd_dnrm2(
    const INT n, const REAL8 *x, const INT incx
) { return dnrm2_(&n, x, &incx); }
static inline REAL4 isvd_scnrm2(
    const INT n, const COMP4 *x, const INT incx
) { return scnrm2_(&n, x, &incx); }
static inline REAL8 isvd_dznrm2(
    const INT n, const COMP8 *x, const INT incx
) { return dznrm2_(&n, x, &incx); }
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  src_la_blas_module
/// Computes the sum of magnitudes of the vector elements.
//\{
static inline REAL4 isvd_sasum(
    const INT n, const REAL4 *x, const INT incx
) { return  sasum_(&n, x, &incx); }
static inline REAL8 isvd_dasum(
    const INT n, const REAL8 *x, const INT incx
) { return  dasum_(&n, x, &incx); }
static inline REAL4 isvd_scasum(
    const INT n, const COMP4 *x, const INT incx
) { return scasum_(&n, x, &incx); }
static inline REAL8 isvd_dzasum(
    const INT n, const COMP8 *x, const INT incx
) { return dzasum_(&n, x, &incx); }
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  src_la_blas_module
/// Computes the product of a vector by a scalar.
//\{
static inline void isvd_sscal(
    const INT n, const REAL4 alpha, REAL4 *x, const INT incx
) { sscal_(&n, &alpha, x, &incx); }
static inline void isvd_dscal(
    const INT n, const REAL8 alpha, REAL8 *x, const INT incx
) { dscal_(&n, &alpha, x, &incx); }
static inline void isvd_cscal(
    const INT n, const COMP4 alpha, COMP4 *x, const INT incx
) { cscal_(&n, &alpha, x, &incx); }
static inline void isvd_zscal(
    const INT n, const COMP8 alpha, COMP8 *x, const INT incx
) { zscal_(&n, &alpha, x, &incx); }
static inline void isvd_csscal(
    const INT n, const REAL4 alpha, COMP4 *x, const INT incx
) { csscal_(&n, &alpha, x, &incx); }
static inline void isvd_zdscal(
    const INT n, const REAL8 alpha, COMP8 *x, const INT incx
) { zdscal_(&n, &alpha, x, &incx); }
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

#endif  // _LIBISVD_LA_BLAS_BLAS1_H_
