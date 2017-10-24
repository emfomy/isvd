////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/blas/dism.c
/// \brief      The BLAS-Like Dism routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/la/blas/blas_like.h>
#include <libisvd/la/def.h>
#include <isvd/la/vml/power_root.h>
#include <libisvd/util/arg.h>

#define isvd_xDism( side, m, n, alpha, a, b, ldb, xScal, xDiv ) \
  const char side_ = isvd_arg2char("SIDE", side, "LR", NULL); \
  if ( !side_ ) return; \
  switch ( side_ ) { \
    case 'L': { \
      for ( isvd_int_t j = 0; j < n; ++j ) { \
        xDiv(m, b+j*ldb, a, b+j*ldb); \
        xScal(m, alpha, b+j*ldb, 1); \
      } \
      break; \
    } \
    case 'R': { \
      for ( isvd_int_t j = 0; j < n; ++j ) { \
        xScal(m, alpha / a[j], b+j*ldb, 1); \
      } \
      break; \
    } \
    default: { \
      isvd_assert_fail(); \
    } \
  }

void isvd_sDism(
    const char side, const isvd_int_t m, const isvd_int_t n, const isvd_s_val_t alpha, const isvd_s_val_t *a, isvd_s_val_t *b,
    const isvd_int_t ldb
) { isvd_xDism(side, m, n, alpha, a, b, ldb, isvd_sScal, isvd_vsDiv); }
void isvd_dDism(
    const char side, const isvd_int_t m, const isvd_int_t n, const isvd_d_val_t alpha, const isvd_d_val_t *a, isvd_d_val_t *b,
    const isvd_int_t ldb
) { isvd_xDism(side, m, n, alpha, a, b, ldb, isvd_dScal, isvd_vdDiv); }
void isvd_cDism(
    const char side, const isvd_int_t m, const isvd_int_t n, const isvd_c_val_t alpha, const isvd_c_val_t *a, isvd_c_val_t *b,
    const isvd_int_t ldb
) { isvd_xDism(side, m, n, alpha, a, b, ldb, isvd_cScal, isvd_vcDiv); }
void isvd_zDism(
    const char side, const isvd_int_t m, const isvd_int_t n, const isvd_z_val_t alpha, const isvd_z_val_t *a, isvd_z_val_t *b,
    const isvd_int_t ldb
) { isvd_xDism(side, m, n, alpha, a, b, ldb, isvd_zScal, isvd_vzDiv); }
