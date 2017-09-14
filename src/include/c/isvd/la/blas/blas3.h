////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/blas/blas3.h
/// \brief      The BLAS level 3 header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef ISVD_LA_BLAS_BLAS3_H_
#define ISVD_LA_BLAS_BLAS3_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

@ISVD_TYPE_MACRO_DEFINE@

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
/// \ingroup  c_la_blas_3_module
/// \brief  Computes a matrix-matrix product with general matrices.
//\{
static inline void isvd_sGemm(
    const CHAR1 transa, const CHAR1 transb, const INT m, const INT n, const INT k, const REAL4 alpha, const REAL4 *a,
    const INT lda, const REAL4 *b, const INT ldb, const REAL4 beta, REAL4 *c, const INT ldc
) { sgemm_(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_dGemm(
    const CHAR1 transa, const CHAR1 transb, const INT m, const INT n, const INT k, const REAL8 alpha, const REAL8 *a,
    const INT lda, const REAL8 *b, const INT ldb, const REAL8 beta, REAL8 *c, const INT ldc
) { dgemm_(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_cGemm(
    const CHAR1 transa, const CHAR1 transb, const INT m, const INT n, const INT k, const COMP4 alpha, const COMP4 *a,
    const INT lda, const COMP4 *b, const INT ldb, const COMP4 beta, COMP4 *c, const INT ldc
) { cgemm_(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_zGemm(
    const CHAR1 transa, const CHAR1 transb, const INT m, const INT n, const INT k, const COMP8 alpha, const COMP8 *a,
    const INT lda, const COMP8 *b, const INT ldb, const COMP8 beta, COMP8 *c, const INT ldc
) { zgemm_(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_3_module
/// \brief  Computes a matrix-matrix product where one input matrix is symmetric/Hermitian.
//\{
static inline void isvd_sSymm(
    const CHAR1 side, const CHAR1 uplo, const INT m, const INT n, const REAL4 alpha, const REAL4 *a, const INT lda,
    const REAL4 *b, const INT ldb, const REAL4 beta, REAL4 *c, const INT ldc
) { ssymm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_dSymm(
    const CHAR1 side, const CHAR1 uplo, const INT m, const INT n, const REAL8 alpha, const REAL8 *a, const INT lda,
    const REAL8 *b, const INT ldb, const REAL8 beta, REAL8 *c, const INT ldc
) { dsymm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_cSymm(
    const CHAR1 side, const CHAR1 uplo, const INT m, const INT n, const COMP4 alpha, const COMP4 *a, const INT lda,
    const COMP4 *b, const INT ldb, const COMP4 beta, COMP4 *c, const INT ldc
) { chemm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_zSymm(
    const CHAR1 side, const CHAR1 uplo, const INT m, const INT n, const COMP8 alpha, const COMP8 *a, const INT lda,
    const COMP8 *b, const INT ldb, const COMP8 beta, COMP8 *c, const INT ldc
) { zhemm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_3_module
/// \brief  Performs a symmetric/Hermitian rank-k update.
//\{
static inline void isvd_sSyrk(
    const CHAR1 uplo, const CHAR1 trans, const INT n, const INT k, const REAL4 alpha, const REAL4 *a, const INT lda,
    const REAL4 beta, REAL4 *c, const INT ldc
) { ssyrk_(&uplo, &trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); }
static inline void isvd_dSyrk(
    const CHAR1 uplo, const CHAR1 trans, const INT n, const INT k, const REAL8 alpha, const REAL8 *a, const INT lda,
    const REAL8 beta, REAL8 *c, const INT ldc
) { dsyrk_(&uplo, &trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); }
static inline void isvd_cSyrk(
    const CHAR1 uplo, const CHAR1 trans, const INT n, const INT k, const REAL4 alpha, const COMP4 *a, const INT lda,
    const REAL4 beta, COMP4 *c, const INT ldc
) { cherk_(&uplo, &trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); }
static inline void isvd_zSyrk(
    const CHAR1 uplo, const CHAR1 trans, const INT n, const INT k, const REAL8 alpha, const COMP8 *a, const INT lda,
    const REAL8 beta, COMP8 *c, const INT ldc
) { zherk_(&uplo, &trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); }
//\}

@ISVD_TYPE_MACRO_UNDEF@

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_LA_BLAS_BLAS3_H_
