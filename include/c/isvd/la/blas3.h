////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/la/blas3.h
/// @brief   The BLAS level 3 header.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_LA_BLAS3_H_
#define _ISVD_LA_BLAS3_H_

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

extern void sgemm();
extern void dgemm();
extern void cgemm();
extern void zgemm();

extern void ssymm();
extern void dsymm();
extern void chemm();
extern void zhemm();

extern void ssyrk();
extern void dsyrk();
extern void cherk();
extern void zherk();

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_USE_MKL

#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_blas_module
/// Computes a matrix-matrix product with general matrices.
//@{
static inline void isvd_sgemm(
    const CHAR1 transa, const CHAR1 transb, const INT m, const INT n, const INT k, const REAL4 alpha, const REAL4 *a,
    const INT lda, const REAL4 *b, const INT ldb, const REAL4 beta, REAL4 *c, const INT ldc
) { sgemm(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_dgemm(
    const CHAR1 transa, const CHAR1 transb, const INT m, const INT n, const INT k, const REAL8 alpha, const REAL8 *a,
    const INT lda, const REAL8 *b, const INT ldb, const REAL8 beta, REAL8 *c, const INT ldc
) { dgemm(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_cgemm(
    const CHAR1 transa, const CHAR1 transb, const INT m, const INT n, const INT k, const COMP4 alpha, const COMP4 *a,
    const INT lda, const COMP4 *b, const INT ldb, const COMP4 beta, COMP4 *c, const INT ldc
) { cgemm(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_zgemm(
    const CHAR1 transa, const CHAR1 transb, const INT m, const INT n, const INT k, const COMP8 alpha, const COMP8 *a,
    const INT lda, const COMP8 *b, const INT ldb, const COMP8 beta, COMP8 *c, const INT ldc
) { zgemm(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_blas_module
/// Computes a matrix-matrix product where one input matrix is symmetric/Hermitian.
//@{
static inline void isvd_ssymm(
    const CHAR1 side, const CHAR1 uplo, const INT m, const INT n, const REAL4 alpha, const REAL4 *a, const INT lda,
    const REAL4 *b, const INT ldb, const REAL4 beta, REAL4 *c, const INT ldc
) { ssymm(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_dsymm(
    const CHAR1 side, const CHAR1 uplo, const INT m, const INT n, const REAL8 alpha, const REAL8 *a, const INT lda,
    const REAL8 *b, const INT ldb, const REAL8 beta, REAL8 *c, const INT ldc
) { dsymm(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_chemm(
    const CHAR1 side, const CHAR1 uplo, const INT m, const INT n, const COMP4 alpha, const COMP4 *a, const INT lda,
    const COMP4 *b, const INT ldb, const COMP4 beta, COMP4 *c, const INT ldc
) { chemm(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_zhemm(
    const CHAR1 side, const CHAR1 uplo, const INT m, const INT n, const COMP8 alpha, const COMP8 *a, const INT lda,
    const COMP8 *b, const INT ldb, const COMP8 beta, COMP8 *c, const INT ldc
) { zhemm(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_blas_module
/// Performs a symmetric/Hermitian rank-k update.
//@{
static inline void isvd_ssyrk(
    const CHAR1 uplo, const CHAR1 trans, const INT n, const INT k, const REAL4 alpha, const REAL4 *a, const INT lda,
    const REAL4 beta, REAL4 *c, const INT ldc
) { ssyrk(&uplo, &trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); }
static inline void isvd_dsyrk(
    const CHAR1 uplo, const CHAR1 trans, const INT n, const INT k, const REAL8 alpha, const REAL8 *a, const INT lda,
    const REAL8 beta, REAL8 *c, const INT ldc
) { dsyrk(&uplo, &trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); }
static inline void isvd_cherk(
    const CHAR1 uplo, const CHAR1 trans, const INT n, const INT k, const REAL4 alpha, const COMP4 *a, const INT lda,
    const REAL4 beta, COMP4 *c, const INT ldc
) { cherk(&uplo, &trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); }
static inline void isvd_zherk(
    const CHAR1 uplo, const CHAR1 trans, const INT n, const INT k, const REAL8 alpha, const COMP8 *a, const INT lda,
    const REAL8 beta, COMP8 *c, const INT ldc
) { zherk(&uplo, &trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); }
//@}

#undef CHAR1
#undef INT
#undef REAL4
#undef REAL8
#undef COMP4
#undef COMP8

#endif  // _ISVD_LA_BLAS3_H_
