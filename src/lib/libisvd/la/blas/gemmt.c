////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/blas/gemmt.c
/// \brief      The BLAS-Like Gemmt routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/la/blas/blas_like.h>
#include <libisvd/la/def.h>
#include <libisvd/util/arg.h>

#if defined(ISVD_USE_MKL)

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

extern void sgemmt_(ISVD_UNKNOWN);
extern void dgemmt_(ISVD_UNKNOWN);
extern void cgemmt_(ISVD_UNKNOWN);
extern void zgemmt_(ISVD_UNKNOWN);

#endif  // DOXYGEN_SHOULD_SKIP_THIS

#if defined(__cplusplus)
}
#endif  // __cplusplus

void isvd_sGemmt(
    const char uplo, const char transa, const char transb, const isvd_int_t n, const isvd_int_t k, const isvd_s_val_t alpha,
    const isvd_s_val_t *a, const isvd_int_t lda, const isvd_s_val_t *b, const isvd_int_t ldb, const isvd_s_val_t beta,
    isvd_s_val_t *c, const isvd_int_t ldc
) { sgemmt(&uplo, &transa, &transb, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
void isvd_dGemmt(
    const char uplo, const char transa, const char transb, const isvd_int_t n, const isvd_int_t k, const isvd_d_val_t alpha,
    const isvd_d_val_t *a, const isvd_int_t lda, const isvd_d_val_t *b, const isvd_int_t ldb, const isvd_d_val_t beta,
    isvd_d_val_t *c, const isvd_int_t ldc
) { dgemmt(&uplo, &transa, &transb, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
void isvd_cGemmt(
    const char uplo, const char transa, const char transb, const isvd_int_t n, const isvd_int_t k, const isvd_c_val_t alpha,
    const isvd_c_val_t *a, const isvd_int_t lda, const isvd_c_val_t *b, const isvd_int_t ldb, const isvd_c_val_t beta,
    isvd_c_val_t *c, const isvd_int_t ldc
) { cgemmt(&uplo, &transa, &transb, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
void isvd_zGemmt(
    const char uplo, const char transa, const char transb, const isvd_int_t n, const isvd_int_t k, const isvd_z_val_t alpha,
    const isvd_z_val_t *a, const isvd_int_t lda, const isvd_z_val_t *b, const isvd_int_t ldb, const isvd_z_val_t beta,
    isvd_z_val_t *c, const isvd_int_t ldc
) { zgemmt(&uplo, &transa, &transb, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }

#else  // ISVD_USE_MKL

#include <isvd/la/blas/blas3.h>

void isvd_sGemmt(
    const char uplo, const char transa, const char transb, const isvd_int_t n, const isvd_int_t k, const isvd_s_val_t alpha,
    const isvd_s_val_t *a, const isvd_int_t lda, const isvd_s_val_t *b, const isvd_int_t ldb, const isvd_s_val_t beta,
    isvd_s_val_t *c, const isvd_int_t ldc
) { ISVD_UNUSED(uplo); sgemm_(&transa, &transb, &n, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
void isvd_dGemmt(
    const char uplo, const char transa, const char transb, const isvd_int_t n, const isvd_int_t k, const isvd_d_val_t alpha,
    const isvd_d_val_t *a, const isvd_int_t lda, const isvd_d_val_t *b, const isvd_int_t ldb, const isvd_d_val_t beta,
    isvd_d_val_t *c, const isvd_int_t ldc
) { ISVD_UNUSED(uplo); dgemm_(&transa, &transb, &n, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
void isvd_cGemmt(
    const char uplo, const char transa, const char transb, const isvd_int_t n, const isvd_int_t k, const isvd_c_val_t alpha,
    const isvd_c_val_t *a, const isvd_int_t lda, const isvd_c_val_t *b, const isvd_int_t ldb, const isvd_c_val_t beta,
    isvd_c_val_t *c, const isvd_int_t ldc
) { ISVD_UNUSED(uplo); cgemm_(&transa, &transb, &n, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
void isvd_zGemmt(
    const char uplo, const char transa, const char transb, const isvd_int_t n, const isvd_int_t k, const isvd_z_val_t alpha,
    const isvd_z_val_t *a, const isvd_int_t lda, const isvd_z_val_t *b, const isvd_int_t ldb, const isvd_z_val_t beta,
    isvd_z_val_t *c, const isvd_int_t ldc
) { ISVD_UNUSED(uplo); zgemm_(&transa, &transb, &n, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }

#endif  // ISVD_USE_MKL
