////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/la/blas1.h
/// @brief   The BLAS level 1 header.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_LA_BLAS1_H_
#define _ISVD_LA_BLAS1_H_

#include <isvd/def.h>

#define CHAR1 char
#define INT   isvd_int_t
#define REAL4 float
#define REAL8 double
#define COMP4 float complex
#define COMP8 double complex

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

#if !defined(ISVD_USE_MKL)

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

extern REAL4 sdot();
extern REAL8 ddot();

extern REAL4 snrm2();
extern REAL8 dnrm2();
extern REAL4 scnrm2();
extern REAL8 dznrm2();

extern REAL4 sasum();
extern REAL8 dasum();
extern REAL4 scasum();
extern REAL8 dzasum();

extern void sscal();
extern void dscal();
extern void cscal();
extern void zscal();
extern void csscal();
extern void zdscal();

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_USE_MKL

#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_blas_module
/// Computes a vector-vector dot product.
//@{
static inline REAL4 isvd_sdot(
    const INT n, const REAL4 *x, const INT incx, REAL4 *y, const INT incy
) { return sdot(&n, x, &incx, y, &incy); }
static inline REAL8 isvd_ddot(
    const INT n, const REAL8 *x, const INT incx, REAL8 *y, const INT incy
) { return ddot(&n, x, &incx, y, &incy); }
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_blas_module
/// Computes the Euclidean norm of a vector.
//@{
static inline REAL4 isvd_snrm2(
    const INT n, const REAL4 *x, const INT incx
) { return snrm2(&n, x, &incx); }
static inline REAL8 isvd_dnrm2(
    const INT n, const REAL8 *x, const INT incx
) { return dnrm2(&n, x, &incx); }
static inline REAL4 isvd_scnrm2(
    const INT n, const COMP4 *x, const INT incx
) { return scnrm2(&n, x, &incx); }
static inline REAL8 isvd_dznrm2(
    const INT n, const COMP8 *x, const INT incx
) { return dznrm2(&n, x, &incx); }
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_blas_module
/// Computes the sum of magnitudes of the vector elements.
//@{
static inline REAL4 isvd_sasum(
    const INT n, const REAL4 *x, const INT incx
) { return  sasum(&n, x, &incx); }
static inline REAL8 isvd_dasum(
    const INT n, const REAL8 *x, const INT incx
) { return  dasum(&n, x, &incx); }
static inline REAL4 isvd_scasum(
    const INT n, const COMP4 *x, const INT incx
) { return scasum(&n, x, &incx); }
static inline REAL8 isvd_dzasum(
    const INT n, const COMP8 *x, const INT incx
) { return dzasum(&n, x, &incx); }
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_blas_module
/// Computes the product of a vector by a scalar.
//@{
static inline void isvd_sscal(
    const INT n, const REAL4 alpha, REAL4 *x, const INT incx
) { sscal(&n, &alpha, x, &incx); }
static inline void isvd_dscal(
    const INT n, const REAL8 alpha, REAL8 *x, const INT incx
) { dscal(&n, &alpha, x, &incx); }
static inline void isvd_cscal(
    const INT n, const COMP4 alpha, COMP4 *x, const INT incx
) { cscal(&n, &alpha, x, &incx); }
static inline void isvd_zscal(
    const INT n, const COMP8 alpha, COMP8 *x, const INT incx
) { zscal(&n, &alpha, x, &incx); }
static inline void isvd_csscal(
    const INT n, const REAL4 alpha, COMP4 *x, const INT incx
) { csscal(&n, &alpha, x, &incx); }
static inline void isvd_zdscal(
    const INT n, const REAL8 alpha, COMP8 *x, const INT incx
) { zdscal(&n, &alpha, x, &incx); }
//@}

#undef CHAR1
#undef INT
#undef REAL4
#undef REAL8
#undef COMP4
#undef COMP8

#endif  // _ISVD_LA_BLAS1_H_
