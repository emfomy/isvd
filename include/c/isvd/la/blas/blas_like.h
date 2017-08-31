////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/blas/blas_like.h
/// \brief      The BLAS-like header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _ISVD_LA_BLAS_BLAS_LIKE_H_
#define _ISVD_LA_BLAS_BLAS_LIKE_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

@ISVD_LA_BLAS_TYPE_DEFINE@

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_module
/// Performs scaling and out-place transposition/copying of matrices.
//\{
void isvd_sOmatcopy(
    const CHAR1 trans, const INT m, const INT n, const REAL4 alpha, const REAL4 *a, const INT lda, REAL4 *b, const INT ldb
);
void isvd_dOmatcopy(
    const CHAR1 trans, const INT m, const INT n, const REAL8 alpha, const REAL8 *a, const INT lda, REAL8 *b, const INT ldb
);
void isvd_cOmatcopy(
    const CHAR1 trans, const INT m, const INT n, const COMP4 alpha, const COMP4 *a, const INT lda, COMP4 *b, const INT ldb
);
void isvd_zOmatcopy(
    const CHAR1 trans, const INT m, const INT n, const COMP8 alpha, const COMP8 *a, const INT lda, COMP8 *b, const INT ldb
);
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_blas_module
/// Computes a matrix-matrix product with general matrices but updates only the upper or lower triangular part of the result
/// matrix.
///
/// \attention  This routine calls \ref isvd_sGemm "isvd_?Gemm" if no MKL support.
//\{
void isvd_sGemmt(
    const CHAR1 uplo, const CHAR1 transa, const CHAR1 transb, const INT n, const INT k, const REAL4 alpha, const REAL4 *a,
    const INT lda, const REAL4 *b, const INT ldb, const REAL4 beta, REAL4 *c, const INT ldc
);
void isvd_dGemmt(
    const CHAR1 uplo, const CHAR1 transa, const CHAR1 transb, const INT n, const INT k, const REAL8 alpha, const REAL8 *a,
    const INT lda, const REAL8 *b, const INT ldb, const REAL8 beta, REAL8 *c, const INT ldc
);
void isvd_cGemmt(
    const CHAR1 uplo, const CHAR1 transa, const CHAR1 transb, const INT n, const INT k, const COMP4 alpha, const COMP4 *a,
    const INT lda, const COMP4 *b, const INT ldb, const COMP4 beta, COMP4 *c, const INT ldc
);
void isvd_zGemmt(
    const CHAR1 uplo, const CHAR1 transa, const CHAR1 transb, const INT n, const INT k, const COMP8 alpha, const COMP8 *a,
    const INT lda, const COMP8 *b, const INT ldb, const COMP8 beta, COMP8 *c, const INT ldc
);
//\}

@ISVD_LA_BLAS_TYPE_UNDEF@

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_LA_BLAS_BLAS_LIKE_H_
