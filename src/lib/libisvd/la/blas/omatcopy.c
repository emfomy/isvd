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
    const char trans, const isvd_int_t m, const isvd_int_t n, const isvd_s_val_t alpha, const isvd_s_val_t *a,
    const isvd_int_t lda, isvd_s_val_t *b, const isvd_int_t ldb
) { mkl_somatcopy_("C", &trans, &m, &n, &alpha, a, &lda, b, &ldb); }
void isvd_dOmatcopy(
    const char trans, const isvd_int_t m, const isvd_int_t n, const isvd_d_val_t alpha, const isvd_d_val_t *a,
    const isvd_int_t lda, isvd_d_val_t *b, const isvd_int_t ldb
) { mkl_domatcopy_("C", &trans, &m, &n, &alpha, a, &lda, b, &ldb); }
void isvd_cOmatcopy(
    const char trans, const isvd_int_t m, const isvd_int_t n, const isvd_c_val_t alpha, const isvd_c_val_t *a,
    const isvd_int_t lda, isvd_c_val_t *b, const isvd_int_t ldb
) { mkl_comatcopy_("C", &trans, &m, &n, &alpha, a, &lda, b, &ldb); }
void isvd_zOmatcopy(
    const char trans, const isvd_int_t m, const isvd_int_t n, const isvd_z_val_t alpha, const isvd_z_val_t *a,
    const isvd_int_t lda, isvd_z_val_t *b, const isvd_int_t ldb
) { mkl_zomatcopy_("C", &trans, &m, &n, &alpha, a, &lda, b, &ldb); }

#else  // ISVD_USE_MKL

static inline isvd_s_val_t rconjf( const isvd_s_val_t z ) { return z; }
static inline isvd_d_val_t rconj(  const isvd_d_val_t z ) { return z; }

#define isvd_xOmatcopy( trans, m, n, alpha, a, lda, b, ldb, conj ) \
  const char trans_ = isvd_arg2char("TRANS", trans, "NTRC", NULL); \
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
    const char trans, const isvd_int_t m, const isvd_int_t n, const isvd_s_val_t alpha, const isvd_s_val_t *a,
    const isvd_int_t lda, isvd_s_val_t *b, const isvd_int_t ldb
) { isvd_xOmatcopy(trans, m, n, alpha, a, lda, b, ldb, rconjf); }
void isvd_dOmatcopy(
    const char trans, const isvd_int_t m, const isvd_int_t n, const isvd_d_val_t alpha, const isvd_d_val_t *a,
    const isvd_int_t lda, isvd_d_val_t *b, const isvd_int_t ldb
) { isvd_xOmatcopy(trans, m, n, alpha, a, lda, b, ldb, rconj); }
void isvd_cOmatcopy(
    const char trans, const isvd_int_t m, const isvd_int_t n, const isvd_c_val_t alpha, const isvd_c_val_t *a,
    const isvd_int_t lda, isvd_c_val_t *b, const isvd_int_t ldb
) { isvd_xOmatcopy(trans, m, n, alpha, a, lda, b, ldb, conjf); }
void isvd_zOmatcopy(
    const char trans, const isvd_int_t m, const isvd_int_t n, const isvd_z_val_t alpha, const isvd_z_val_t *a,
    const isvd_int_t lda, isvd_z_val_t *b, const isvd_int_t ldb
) { isvd_xOmatcopy(trans, m, n, alpha, a, lda, b, ldb, conj); }

#endif  // ISVD_USE_MKL
