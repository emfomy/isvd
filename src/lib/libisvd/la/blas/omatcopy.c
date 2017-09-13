////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/blas/omatcopy.c
/// \brief      The BLAS-Like Omatcopy routine.
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

extern void mkl_somatcopy_(ISVD_UNKNOWN);
extern void mkl_domatcopy_(ISVD_UNKNOWN);
extern void mkl_comatcopy_(ISVD_UNKNOWN);
extern void mkl_zomatcopy_(ISVD_UNKNOWN);

#endif  // DOXYGEN_SHOULD_SKIP_THIS

#if defined(__cplusplus)
}
#endif  // __cplusplus

void isvd_sOmatcopy(
    const CHAR1 trans, const INT m, const INT n, const REAL4 alpha, const REAL4 *a, const INT lda, REAL4 *b, const INT ldb
) { mkl_somatcopy_("C", &trans, &m, &n, &alpha, a, &lda, b, &ldb); }
void isvd_dOmatcopy(
    const CHAR1 trans, const INT m, const INT n, const REAL8 alpha, const REAL8 *a, const INT lda, REAL8 *b, const INT ldb
) { mkl_domatcopy_("C", &trans, &m, &n, &alpha, a, &lda, b, &ldb); }
void isvd_cOmatcopy(
    const CHAR1 trans, const INT m, const INT n, const COMP4 alpha, const COMP4 *a, const INT lda, COMP4 *b, const INT ldb
) { mkl_comatcopy_("C", &trans, &m, &n, &alpha, a, &lda, b, &ldb); }
void isvd_zOmatcopy(
    const CHAR1 trans, const INT m, const INT n, const COMP8 alpha, const COMP8 *a, const INT lda, COMP8 *b, const INT ldb
) { mkl_zomatcopy_("C", &trans, &m, &n, &alpha, a, &lda, b, &ldb); }

#else  // ISVD_USE_MKL

static inline float  rconjf( const float  z ) { return z; }
static inline double rconj(  const double z ) { return z; }

#define isvd_xOmatcopy( trans, m, n, alpha, a, lda, b, ldb, conj ) \
  const char trans_ = isvd_arg2char("TRANS", trans, "NTRC", nullptr); \
  if ( !trans_ ) return; \
  switch ( trans_ ) { \
    case 'N': { \
      for ( isvd_int_t j = 0; j < n; ++j ) { \
        for ( isvd_int_t i = 0; i < m; ++i ) { \
          b[i+j*ldb] = alpha * a[i+j*lda]; \
        } \
      } \
      break; \
    } \
    case 'T': { \
      for ( isvd_int_t j = 0; j < n; ++j ) { \
        for ( isvd_int_t i = 0; i < m; ++i ) { \
          b[i*ldb+j] = alpha * a[i+j*lda]; \
        } \
      } \
      break; \
    } \
    case 'R': { \
      for ( isvd_int_t j = 0; j < n; ++j ) { \
        for ( isvd_int_t i = 0; i < m; ++i ) { \
          b[i+j*ldb] = alpha * conj(a[i+j*lda]); \
        } \
      } \
      break; \
    } \
    case 'C': { \
      for ( isvd_int_t j = 0; j < n; ++j ) { \
        for ( isvd_int_t i = 0; i < m; ++i ) { \
          b[i*ldb+j] = alpha * conj(a[i+j*lda]); \
        } \
      } \
      break; \
    } \
    default: { \
      isvd_assert_fail(); \
    } \
  }

void isvd_sOmatcopy(
    const CHAR1 trans, const INT m, const INT n, const REAL4 alpha, const REAL4 *a, const INT lda, REAL4 *b, const INT ldb
) { isvd_xOmatcopy(trans, m, n, alpha, a, lda, b, ldb, rconjf); }
void isvd_dOmatcopy(
    const CHAR1 trans, const INT m, const INT n, const REAL8 alpha, const REAL8 *a, const INT lda, REAL8 *b, const INT ldb
) { isvd_xOmatcopy(trans, m, n, alpha, a, lda, b, ldb, rconj); }
void isvd_cOmatcopy(
    const CHAR1 trans, const INT m, const INT n, const COMP4 alpha, const COMP4 *a, const INT lda, COMP4 *b, const INT ldb
) { isvd_xOmatcopy(trans, m, n, alpha, a, lda, b, ldb, conjf); }
void isvd_zOmatcopy(
    const CHAR1 trans, const INT m, const INT n, const COMP8 alpha, const COMP8 *a, const INT lda, COMP8 *b, const INT ldb
) { isvd_xOmatcopy(trans, m, n, alpha, a, lda, b, ldb, conj); }

#endif  // ISVD_USE_MKL

@ISVD_LA_BLAS_TYPE_UNDEF@
