////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/la/blas_like.h
/// @brief   The BLAS-like header.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_LA_BLAS_LIKE_H_
#define _ISVD_LA_BLAS_LIKE_H_

#include <isvd/def.h>
#include <isvd/la/blas1.h>
#include <isvd/la/blas2.h>
#include <isvd/la/blas3.h>

#define CHAR1 char
#define INT   isvd_int_t
#define REAL4 float
#define REAL8 double
#define COMP4 float complex
#define COMP8 double complex

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_blas_module
/// Computes a matrix-matrix product with general matrices but updates only the upper or lower triangular part of the result
/// matrix.
//@{
#if defined(ISVD_USE_MKL)
static inline void isvd_sgemmt(
    const CHAR1 uplo, const CHAR1 transa, const CHAR1 transb, const INT n, const INT k, const REAL4 alpha, const REAL4 *a,
    const INT lda, const REAL4 *b, const INT ldb, const REAL4 beta, REAL4 *c, const INT ldc
) { sgemmt(&uplo, &transa, &transb, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_dgemmt(
    const CHAR1 uplo, const CHAR1 transa, const CHAR1 transb, const INT n, const INT k, const REAL8 alpha, const REAL8 *a,
    const INT lda, const REAL8 *b, const INT ldb, const REAL8 beta, REAL8 *c, const INT ldc
) { dgemmt(&uplo, &transa, &transb, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_cgemmt(
    const CHAR1 uplo, const CHAR1 transa, const CHAR1 transb, const INT n, const INT k, const COMP4 alpha, const COMP4 *a,
    const INT lda, const COMP4 *b, const INT ldb, const COMP4 beta, COMP4 *c, const INT ldc
) { cgemmt(&uplo, &transa, &transb, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_zgemmt(
    const CHAR1 uplo, const CHAR1 transa, const CHAR1 transb, const INT n, const INT k, const COMP8 alpha, const COMP8 *a,
    const INT lda, const COMP8 *b, const INT ldb, const COMP8 beta, COMP8 *c, const INT ldc
) { zgemmt(&uplo, &transa, &transb, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
#else  // ISVD_USE_MKL
static inline void isvd_sgemmt(
    const CHAR1 uplo, const CHAR1 transa, const CHAR1 transb, const INT n, const INT k, const REAL4 alpha, const REAL4 *a,
    const INT lda, const REAL4 *b, const INT ldb, const REAL4 beta, REAL4 *c, const INT ldc
) { ISVD_UNUSED(uplo); sgemm(&transa, &transb, &n, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_dgemmt(
    const CHAR1 uplo, const CHAR1 transa, const CHAR1 transb, const INT n, const INT k, const REAL8 alpha, const REAL8 *a,
    const INT lda, const REAL8 *b, const INT ldb, const REAL8 beta, REAL8 *c, const INT ldc
) { ISVD_UNUSED(uplo); dgemm(&transa, &transb, &n, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_cgemmt(
    const CHAR1 uplo, const CHAR1 transa, const CHAR1 transb, const INT n, const INT k, const COMP4 alpha, const COMP4 *a,
    const INT lda, const COMP4 *b, const INT ldb, const COMP4 beta, COMP4 *c, const INT ldc
) { ISVD_UNUSED(uplo); cgemm(&transa, &transb, &n, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_zgemmt(
    const CHAR1 uplo, const CHAR1 transa, const CHAR1 transb, const INT n, const INT k, const COMP8 alpha, const COMP8 *a,
    const INT lda, const COMP8 *b, const INT ldb, const COMP8 beta, COMP8 *c, const INT ldc
) { ISVD_UNUSED(uplo); zgemm(&transa, &transb, &n, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
#endif  // ISVD_USE_MKL
//@}

#undef CHAR1
#undef INT
#undef REAL4
#undef REAL8
#undef COMP4
#undef COMP8

#endif  // _ISVD_LA_BLAS_LIKE_H_
