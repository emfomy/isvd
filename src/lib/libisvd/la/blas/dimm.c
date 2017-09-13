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

@ISVD_LA_BLAS_TYPE_DEFINE@

#define isvd_xDimm( side, m, n, alpha, a, b, ldb, xScal, xMul ) \
  const char side_ = isvd_arg2char("SIDE", side, "LR", nullptr); \
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
    const CHAR1 side, const INT m, const INT n, const REAL4 alpha, const REAL4 *a, REAL4 *b, const INT ldb
) { isvd_xDimm(side, m, n, alpha, a, b, ldb, isvd_sScal, isvd_vsMul); }
void isvd_dDimm(
    const CHAR1 side, const INT m, const INT n, const REAL8 alpha, const REAL8 *a, REAL8 *b, const INT ldb
) { isvd_xDimm(side, m, n, alpha, a, b, ldb, isvd_dScal, isvd_vdMul); }
void isvd_cDimm(
    const CHAR1 side, const INT m, const INT n, const COMP4 alpha, const COMP4 *a, COMP4 *b, const INT ldb
) { isvd_xDimm(side, m, n, alpha, a, b, ldb, isvd_cScal, isvd_vcMul); }
void isvd_zDimm(
    const CHAR1 side, const INT m, const INT n, const COMP8 alpha, const COMP8 *a, COMP8 *b, const INT ldb
) { isvd_xDimm(side, m, n, alpha, a, b, ldb, isvd_zScal, isvd_vzMul); }

@ISVD_LA_BLAS_TYPE_UNDEF@
