////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/blas/dimm.c
/// \brief      The BLAS-Like Dimm routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/la/blas/blas_like.h>
#include <libisvd/la/def.h>
#include <isvd/la/vml/mathematical.h>
#include <libisvd/util/arg.h>

#define isvd_xDimm( side, m, n, alpha, a, b, ldb, xScal, xMul ) \
  const char side_ = isvd_arg2char("SIDE", side, "LR", NULL); \
  if ( !side_ ) return; \
  switch ( side_ ) { \
    case 'L': { \
      for ( isvd_int_t j = 0; j < n; ++j ) { \
        xMul(m, a, b+j*ldb, b+j*ldb); \
        xScal(m, alpha, b+j*ldb, 1); \
      } \
      break; \
    } \
    case 'R': { \
      for ( isvd_int_t j = 0; j < n; ++j ) { \
        xScal(m, alpha * a[j], b+j*ldb, 1); \
      } \
      break; \
    } \
    default: { \
      isvd_assert_fail(); \
    } \
  }

void isvd_sDimm(
    const char side, const isvd_int_t m, const isvd_int_t n, const isvd_s_val_t alpha, const isvd_s_val_t *a, isvd_s_val_t *b,
    const isvd_int_t ldb
) { isvd_xDimm(side, m, n, alpha, a, b, ldb, isvd_sScal, isvd_vsMul); }
void isvd_dDimm(
    const char side, const isvd_int_t m, const isvd_int_t n, const isvd_d_val_t alpha, const isvd_d_val_t *a, isvd_d_val_t *b,
    const isvd_int_t ldb
) { isvd_xDimm(side, m, n, alpha, a, b, ldb, isvd_dScal, isvd_vdMul); }
void isvd_cDimm(
    const char side, const isvd_int_t m, const isvd_int_t n, const isvd_c_val_t alpha, const isvd_c_val_t *a, isvd_c_val_t *b,
    const isvd_int_t ldb
) { isvd_xDimm(side, m, n, alpha, a, b, ldb, isvd_cScal, isvd_vcMul); }
void isvd_zDimm(
    const char side, const isvd_int_t m, const isvd_int_t n, const isvd_z_val_t alpha, const isvd_z_val_t *a, isvd_z_val_t *b,
    const isvd_int_t ldb
) { isvd_xDimm(side, m, n, alpha, a, b, ldb, isvd_zScal, isvd_vzMul); }
