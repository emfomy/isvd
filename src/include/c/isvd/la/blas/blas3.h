////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/blas/blas3.h
/// \brief      The BLAS level 3 header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef ISVD_LA_BLAS_BLAS3_H_
#define ISVD_LA_BLAS_BLAS3_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

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
    const char transa, const char transb, const isvd_int_t m, const isvd_int_t n, const isvd_int_t k, const isvd_s_val_t alpha,
    const isvd_s_val_t *a, const isvd_int_t lda, const isvd_s_val_t *b, const isvd_int_t ldb, const isvd_s_val_t beta,
    isvd_s_val_t *c, const isvd_int_t ldc
) { sgemm_(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_dGemm(
    const char transa, const char transb, const isvd_int_t m, const isvd_int_t n, const isvd_int_t k, const isvd_d_val_t alpha,
    const isvd_d_val_t *a, const isvd_int_t lda, const isvd_d_val_t *b, const isvd_int_t ldb, const isvd_d_val_t beta,
    isvd_d_val_t *c, const isvd_int_t ldc
) { dgemm_(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_cGemm(
    const char transa, const char transb, const isvd_int_t m, const isvd_int_t n, const isvd_int_t k, const isvd_c_val_t alpha,
    const isvd_c_val_t *a, const isvd_int_t lda, const isvd_c_val_t *b, const isvd_int_t ldb, const isvd_c_val_t beta,
    isvd_c_val_t *c, const isvd_int_t ldc
) { cgemm_(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_zGemm(
    const char transa, const char transb, const isvd_int_t m, const isvd_int_t n, const isvd_int_t k, const isvd_z_val_t alpha,
    const isvd_z_val_t *a, const isvd_int_t lda, const isvd_z_val_t *b, const isvd_int_t ldb, const isvd_z_val_t beta,
    isvd_z_val_t *c, const isvd_int_t ldc
) { zgemm_(&transa, &transb, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_3_module
/// \brief  Computes a matrix-matrix product where one input matrix is symmetric/Hermitian.
//\{
static inline void isvd_sSymm(
    const char side, const char uplo, const isvd_int_t m, const isvd_int_t n, const isvd_s_val_t alpha, const isvd_s_val_t *a,
    const isvd_int_t lda, const isvd_s_val_t *b, const isvd_int_t ldb, const isvd_s_val_t beta, isvd_s_val_t *c,
    const isvd_int_t ldc
) { ssymm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_dSymm(
    const char side, const char uplo, const isvd_int_t m, const isvd_int_t n, const isvd_d_val_t alpha, const isvd_d_val_t *a,
    const isvd_int_t lda, const isvd_d_val_t *b, const isvd_int_t ldb, const isvd_d_val_t beta, isvd_d_val_t *c,
    const isvd_int_t ldc
) { dsymm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_cSymm(
    const char side, const char uplo, const isvd_int_t m, const isvd_int_t n, const isvd_c_val_t alpha, const isvd_c_val_t *a,
    const isvd_int_t lda, const isvd_c_val_t *b, const isvd_int_t ldb, const isvd_c_val_t beta, isvd_c_val_t *c,
    const isvd_int_t ldc
) { chemm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
static inline void isvd_zSymm(
    const char side, const char uplo, const isvd_int_t m, const isvd_int_t n, const isvd_z_val_t alpha, const isvd_z_val_t *a,
    const isvd_int_t lda, const isvd_z_val_t *b, const isvd_int_t ldb, const isvd_z_val_t beta, isvd_z_val_t *c,
    const isvd_int_t ldc
) { zhemm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_3_module
/// \brief  Performs a symmetric/Hermitian rank-k update.
//\{
static inline void isvd_sSyrk(
    const char uplo, const char trans, const isvd_int_t n, const isvd_int_t k, const isvd_s_val_t alpha, const isvd_s_val_t *a,
    const isvd_int_t lda, const isvd_s_val_t beta, isvd_s_val_t *c, const isvd_int_t ldc
) { ssyrk_(&uplo, &trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); }
static inline void isvd_dSyrk(
    const char uplo, const char trans, const isvd_int_t n, const isvd_int_t k, const isvd_d_val_t alpha, const isvd_d_val_t *a,
    const isvd_int_t lda, const isvd_d_val_t beta, isvd_d_val_t *c, const isvd_int_t ldc
) { dsyrk_(&uplo, &trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); }
static inline void isvd_cSyrk(
    const char uplo, const char trans, const isvd_int_t n, const isvd_int_t k, const isvd_s_val_t alpha, const isvd_c_val_t *a,
    const isvd_int_t lda, const isvd_s_val_t beta, isvd_c_val_t *c, const isvd_int_t ldc
) { cherk_(&uplo, &trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); }
static inline void isvd_zSyrk(
    const char uplo, const char trans, const isvd_int_t n, const isvd_int_t k, const isvd_d_val_t alpha, const isvd_z_val_t *a,
    const isvd_int_t lda, const isvd_d_val_t beta, isvd_z_val_t *c, const isvd_int_t ldc
) { zherk_(&uplo, &trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); }
//\}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_LA_BLAS_BLAS3_H_
