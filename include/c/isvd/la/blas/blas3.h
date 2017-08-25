////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/la/blas/blas3.h
/// @brief   The BLAS level 3 header.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_LA_BLAS_BLAS3_H_
#define _ISVD_LA_BLAS_BLAS3_H_

#include <isvd/def.h>

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

extern void sgemm_(ISVD_UNKNOWN);
extern void dgemm_(ISVD_UNKNOWN);
extern void cgemm_(ISVD_UNKNOWN);
extern void zgemm_(ISVD_UNKNOWN);

extern void ssymm_(ISVD_UNKNOWN);
extern void dsymm_(ISVD_UNKNOWN);
extern void chemm_(ISVD_UNKNOWN);
extern void zhemm_(ISVD_UNKNOWN);

extern void ssyrk_(ISVD_UNKNOWN);
extern void dsyrk_(ISVD_UNKNOWN);
extern void cherk_(ISVD_UNKNOWN);
extern void zherk_(ISVD_UNKNOWN);

#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_blas_module
/// Computes a matrix-matrix product with general matrices.
//@{
static inline void isvd_sgemm(
    const CHAR1 transa, const CHAR1 transb, const INT m, const INT n, const INT k, const REAL4 alpha, const REAL4 *a,
    const INT lda, const REAL4 *b, const INT ldb, const REAL4 beta, REAL4 *c, const INT ldc
) { sgemm_(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_dgemm(
    const CHAR1 transa, const CHAR1 transb, const INT m, const INT n, const INT k, const REAL8 alpha, const REAL8 *a,
    const INT lda, const REAL8 *b, const INT ldb, const REAL8 beta, REAL8 *c, const INT ldc
) { dgemm_(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_cgemm(
    const CHAR1 transa, const CHAR1 transb, const INT m, const INT n, const INT k, const COMP4 alpha, const COMP4 *a,
    const INT lda, const COMP4 *b, const INT ldb, const COMP4 beta, COMP4 *c, const INT ldc
) { cgemm_(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_zgemm(
    const CHAR1 transa, const CHAR1 transb, const INT m, const INT n, const INT k, const COMP8 alpha, const COMP8 *a,
    const INT lda, const COMP8 *b, const INT ldb, const COMP8 beta, COMP8 *c, const INT ldc
) { zgemm_(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_blas_module
/// Computes a matrix-matrix product where one input matrix is symmetric/Hermitian.
//@{
static inline void isvd_ssymm(
    const CHAR1 side, const CHAR1 uplo, const INT m, const INT n, const REAL4 alpha, const REAL4 *a, const INT lda,
    const REAL4 *b, const INT ldb, const REAL4 beta, REAL4 *c, const INT ldc
) { ssymm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_dsymm(
    const CHAR1 side, const CHAR1 uplo, const INT m, const INT n, const REAL8 alpha, const REAL8 *a, const INT lda,
    const REAL8 *b, const INT ldb, const REAL8 beta, REAL8 *c, const INT ldc
) { dsymm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_chemm(
    const CHAR1 side, const CHAR1 uplo, const INT m, const INT n, const COMP4 alpha, const COMP4 *a, const INT lda,
    const COMP4 *b, const INT ldb, const COMP4 beta, COMP4 *c, const INT ldc
) { chemm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_zhemm(
    const CHAR1 side, const CHAR1 uplo, const INT m, const INT n, const COMP8 alpha, const COMP8 *a, const INT lda,
    const COMP8 *b, const INT ldb, const COMP8 beta, COMP8 *c, const INT ldc
) { zhemm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_blas_module
/// Performs a symmetric/Hermitian rank-k update.
//@{
static inline void isvd_ssyrk(
    const CHAR1 uplo, const CHAR1 trans, const INT n, const INT k, const REAL4 alpha, const REAL4 *a, const INT lda,
    const REAL4 beta, REAL4 *c, const INT ldc
) { ssyrk_(&uplo, &trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); }
static inline void isvd_dsyrk(
    const CHAR1 uplo, const CHAR1 trans, const INT n, const INT k, const REAL8 alpha, const REAL8 *a, const INT lda,
    const REAL8 beta, REAL8 *c, const INT ldc
) { dsyrk_(&uplo, &trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); }
static inline void isvd_cherk(
    const CHAR1 uplo, const CHAR1 trans, const INT n, const INT k, const REAL4 alpha, const COMP4 *a, const INT lda,
    const REAL4 beta, COMP4 *c, const INT ldc
) { cherk_(&uplo, &trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); }
static inline void isvd_zherk(
    const CHAR1 uplo, const CHAR1 trans, const INT n, const INT k, const REAL8 alpha, const COMP8 *a, const INT lda,
    const REAL8 beta, COMP8 *c, const INT ldc
) { zherk_(&uplo, &trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); }
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

#endif  // _ISVD_LA_BLAS_BLAS3_H_
