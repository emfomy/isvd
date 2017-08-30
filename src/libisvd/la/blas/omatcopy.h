////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/la/blas/omatcopy.h
/// \brief      The BLAS-like OMATCOPY routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _LIBISVD_LA_BLAS_OMATCOPY_H_
#define _LIBISVD_LA_BLAS_OMATCOPY_H_

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

#if defined(ISVD_USE_MKL)

extern void mkl_somatcopy_(ISVD_UNKNOWN);
extern void mkl_domatcopy_(ISVD_UNKNOWN);
extern void mkl_comatcopy_(ISVD_UNKNOWN);
extern void mkl_zomatcopy_(ISVD_UNKNOWN);

#endif  // ISVD_USE_MKL

#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  src_la_blas_module
/// Performs scaling and out-place transposition/copying of matrices.
//\{
#if defined(ISVD_USE_MKL)
static inline void isvd_somatcopy(
    const CHAR1 trans, const INT m, const INT n, const REAL4 alpha, const REAL4 *a, const INT lda, REAL4 *b, const INT ldb
) { mkl_somatcopy_("C", &trans, &m, &n, &alpha, a, &lda, b, &ldb); }
static inline void isvd_domatcopy(
    const CHAR1 trans, const INT m, const INT n, const REAL8 alpha, const REAL8 *a, const INT lda, REAL8 *b, const INT ldb
) { mkl_domatcopy_("C", &trans, &m, &n, &alpha, a, &lda, b, &ldb); }
static inline void isvd_comatcopy(
    const CHAR1 trans, const INT m, const INT n, const COMP4 alpha, const COMP4 *a, const INT lda, COMP4 *b, const INT ldb
) { mkl_comatcopy_("C", &trans, &m, &n, &alpha, a, &lda, b, &ldb); }
static inline void isvd_zomatcopy(
    const CHAR1 trans, const INT m, const INT n, const COMP8 alpha, const COMP8 *a, const INT lda, COMP8 *b, const INT ldb
) { mkl_zomatcopy_("C", &trans, &m, &n, &alpha, a, &lda, b, &ldb); }
#else  // ISVD_USE_MKL
void isvd_somatcopy(
    const CHAR1 trans, const INT m, const INT n, const REAL4 alpha, const REAL4 *a, const INT lda, REAL4 *b, const INT ldb
);
void isvd_domatcopy(
    const CHAR1 trans, const INT m, const INT n, const REAL8 alpha, const REAL8 *a, const INT lda, REAL8 *b, const INT ldb
);
void isvd_comatcopy(
    const CHAR1 trans, const INT m, const INT n, const COMP4 alpha, const COMP4 *a, const INT lda, COMP4 *b, const INT ldb
);
void isvd_zomatcopy(
    const CHAR1 trans, const INT m, const INT n, const COMP8 alpha, const COMP8 *a, const INT lda, COMP8 *b, const INT ldb
);
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

#endif  // _LIBISVD_LA_BLAS_OMATCOPY_H_
