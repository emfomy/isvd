////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/la/blas/dism.c
/// \brief      The BLAS-Like Dism routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/la/blas/blas_like.h>
#include <libisvd/def.h>
#include <isvd/la/vml/power_root.h>
#include <libisvd/util/arg.h>

@ISVD_LA_BLAS_TYPE_DEFINE@

#define isvd_xDism( side, m, n, alpha, a, b, ldb, xScal, xDiv ) \
  const char side_ = isvd_arg2char("SIDE", side, "LR", nullptr); \
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
    const CHAR1 side, const INT m, const INT n, const REAL4 alpha, const REAL4 *a, REAL4 *b, const INT ldb
) { isvd_xDism(side, m, n, alpha, a, b, ldb, isvd_sScal, isvd_vsDiv); }
void isvd_dDism(
    const CHAR1 side, const INT m, const INT n, const REAL8 alpha, const REAL8 *a, REAL8 *b, const INT ldb
) { isvd_xDism(side, m, n, alpha, a, b, ldb, isvd_dScal, isvd_vdDiv); }
void isvd_cDism(
    const CHAR1 side, const INT m, const INT n, const COMP4 alpha, const COMP4 *a, COMP4 *b, const INT ldb
) { isvd_xDism(side, m, n, alpha, a, b, ldb, isvd_cScal, isvd_vcDiv); }
void isvd_zDism(
    const CHAR1 side, const INT m, const INT n, const COMP8 alpha, const COMP8 *a, COMP8 *b, const INT ldb
) { isvd_xDism(side, m, n, alpha, a, b, ldb, isvd_zScal, isvd_vzDiv); }

@ISVD_LA_BLAS_TYPE_UNDEF@
