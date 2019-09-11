////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/blas/blas_like.h
/// \brief      The BLAS-Like header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef ISVD_LA_BLAS_BLAS_LIKE_H_
#define ISVD_LA_BLAS_BLAS_LIKE_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_like_module
/// \brief  Performs scaling and out-place transposition/copying of matrices.
//\{
void isvd_sOmatcopy(
    const char trans, const isvd_int_t m, const isvd_int_t n, const isvd_s_val_t alpha, const isvd_s_val_t *a,
    const isvd_int_t lda, isvd_s_val_t *b, const isvd_int_t ldb
);
void isvd_dOmatcopy(
    const char trans, const isvd_int_t m, const isvd_int_t n, const isvd_d_val_t alpha, const isvd_d_val_t *a,
    const isvd_int_t lda, isvd_d_val_t *b, const isvd_int_t ldb
);
void isvd_cOmatcopy(
    const char trans, const isvd_int_t m, const isvd_int_t n, const isvd_c_val_t alpha, const isvd_c_val_t *a,
    const isvd_int_t lda, isvd_c_val_t *b, const isvd_int_t ldb
);
void isvd_zOmatcopy(
    const char trans, const isvd_int_t m, const isvd_int_t n, const isvd_z_val_t alpha, const isvd_z_val_t *a,
    const isvd_int_t lda, isvd_z_val_t *b, const isvd_int_t ldb
);
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_like_module
/// \brief  Computes a matrix-matrix product where one input matrix is diagonal.
//\{
void isvd_sDimm(
    const char side, const isvd_int_t m, const isvd_int_t n, const isvd_s_val_t alpha, const isvd_s_val_t *a, isvd_s_val_t *b,
    const isvd_int_t ldb
);
void isvd_dDimm(
    const char side, const isvd_int_t m, const isvd_int_t n, const isvd_d_val_t alpha, const isvd_d_val_t *a, isvd_d_val_t *b,
    const isvd_int_t ldb
);
void isvd_cDimm(
    const char side, const isvd_int_t m, const isvd_int_t n, const isvd_c_val_t alpha, const isvd_c_val_t *a, isvd_c_val_t *b,
    const isvd_int_t ldb
);
void isvd_zDimm(
    const char side, const isvd_int_t m, const isvd_int_t n, const isvd_z_val_t alpha, const isvd_z_val_t *a, isvd_z_val_t *b,
    const isvd_int_t ldb
);
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_like_module
/// \brief  Solves a diagonal matrix equation.
//\{
void isvd_sDism(
    const char side, const isvd_int_t m, const isvd_int_t n, const isvd_s_val_t alpha, const isvd_s_val_t *a, isvd_s_val_t *b,
    const isvd_int_t ldb
);
void isvd_dDism(
    const char side, const isvd_int_t m, const isvd_int_t n, const isvd_d_val_t alpha, const isvd_d_val_t *a, isvd_d_val_t *b,
    const isvd_int_t ldb
);
void isvd_cDism(
    const char side, const isvd_int_t m, const isvd_int_t n, const isvd_c_val_t alpha, const isvd_c_val_t *a, isvd_c_val_t *b,
    const isvd_int_t ldb
);
void isvd_zDism(
    const char side, const isvd_int_t m, const isvd_int_t n, const isvd_z_val_t alpha, const isvd_z_val_t *a, isvd_z_val_t *b,
    const isvd_int_t ldb
);
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_like_module
/// \brief  Computes a matrix-matrix product with general matrices but updates only the upper or lower triangular part of the
///         result matrix.
///
/// \attention  This routine calls \ref isvd_sGemm "isvd_?Gemm" if no MKL support.
//\{
void isvd_sGemmt(
    const char uplo, const char transa, const char transb, const isvd_int_t n, const isvd_int_t k, const isvd_s_val_t alpha,
    const isvd_s_val_t *a, const isvd_int_t lda, const isvd_s_val_t *b, const isvd_int_t ldb, const isvd_s_val_t beta,
    isvd_s_val_t *c, const isvd_int_t ldc
);
void isvd_dGemmt(
    const char uplo, const char transa, const char transb, const isvd_int_t n, const isvd_int_t k, const isvd_d_val_t alpha,
    const isvd_d_val_t *a, const isvd_int_t lda, const isvd_d_val_t *b, const isvd_int_t ldb, const isvd_d_val_t beta,
    isvd_d_val_t *c, const isvd_int_t ldc
);
void isvd_cGemmt(
    const char uplo, const char transa, const char transb, const isvd_int_t n, const isvd_int_t k, const isvd_c_val_t alpha,
    const isvd_c_val_t *a, const isvd_int_t lda, const isvd_c_val_t *b, const isvd_int_t ldb, const isvd_c_val_t beta,
    isvd_c_val_t *c, const isvd_int_t ldc
);
void isvd_zGemmt(
    const char uplo, const char transa, const char transb, const isvd_int_t n, const isvd_int_t k, const isvd_z_val_t alpha,
    const isvd_z_val_t *a, const isvd_int_t lda, const isvd_z_val_t *b, const isvd_int_t ldb, const isvd_z_val_t beta,
    isvd_z_val_t *c, const isvd_int_t ldc
);
//\}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_LA_BLAS_BLAS_LIKE_H_
