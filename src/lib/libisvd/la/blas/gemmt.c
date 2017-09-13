////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/blas/gemmt.c
/// \brief      The BLAS-Like Gemmt routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/la/blas/blas_like.h>
#include <libisvd/la/def.h>
#include <libisvd/util/arg.h>

@ISVD_LA_BLAS_TYPE_DEFINE@

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
    const CHAR1 uplo, const CHAR1 transa, const CHAR1 transb, const INT n, const INT k, const REAL4 alpha, const REAL4 *a,
    const INT lda, const REAL4 *b, const INT ldb, const REAL4 beta, REAL4 *c, const INT ldc
) { sgemmt(&uplo, &transa, &transb, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
void isvd_dGemmt(
    const CHAR1 uplo, const CHAR1 transa, const CHAR1 transb, const INT n, const INT k, const REAL8 alpha, const REAL8 *a,
    const INT lda, const REAL8 *b, const INT ldb, const REAL8 beta, REAL8 *c, const INT ldc
) { dgemmt(&uplo, &transa, &transb, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
void isvd_cGemmt(
    const CHAR1 uplo, const CHAR1 transa, const CHAR1 transb, const INT n, const INT k, const COMP4 alpha, const COMP4 *a,
    const INT lda, const COMP4 *b, const INT ldb, const COMP4 beta, COMP4 *c, const INT ldc
) { cgemmt(&uplo, &transa, &transb, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
void isvd_zGemmt(
    const CHAR1 uplo, const CHAR1 transa, const CHAR1 transb, const INT n, const INT k, const COMP8 alpha, const COMP8 *a,
    const INT lda, const COMP8 *b, const INT ldb, const COMP8 beta, COMP8 *c, const INT ldc
) { zgemmt(&uplo, &transa, &transb, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }

#else  // ISVD_USE_MKL

#include <isvd/la/blas/blas3.h>

void isvd_sGemmt(
    const CHAR1 uplo, const CHAR1 transa, const CHAR1 transb, const INT n, const INT k, const REAL4 alpha, const REAL4 *a,
    const INT lda, const REAL4 *b, const INT ldb, const REAL4 beta, REAL4 *c, const INT ldc
) { ISVD_UNUSED(uplo); sgemm_(&transa, &transb, &n, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
void isvd_dGemmt(
    const CHAR1 uplo, const CHAR1 transa, const CHAR1 transb, const INT n, const INT k, const REAL8 alpha, const REAL8 *a,
    const INT lda, const REAL8 *b, const INT ldb, const REAL8 beta, REAL8 *c, const INT ldc
) { ISVD_UNUSED(uplo); dgemm_(&transa, &transb, &n, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
void isvd_cGemmt(
    const CHAR1 uplo, const CHAR1 transa, const CHAR1 transb, const INT n, const INT k, const COMP4 alpha, const COMP4 *a,
    const INT lda, const COMP4 *b, const INT ldb, const COMP4 beta, COMP4 *c, const INT ldc
) { ISVD_UNUSED(uplo); cgemm_(&transa, &transb, &n, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }
void isvd_zGemmt(
    const CHAR1 uplo, const CHAR1 transa, const CHAR1 transb, const INT n, const INT k, const COMP8 alpha, const COMP8 *a,
    const INT lda, const COMP8 *b, const INT ldb, const COMP8 beta, COMP8 *c, const INT ldc
) { ISVD_UNUSED(uplo); zgemm_(&transa, &transb, &n, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); }

#endif  // ISVD_USE_MKL

@ISVD_LA_BLAS_TYPE_UNDEF@
