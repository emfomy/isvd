////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/blas/iamin.c
/// \brief      The BLAS-1 iAmin routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/la/blas/blas1.h>
#include <libisvd/la/def.h>

@ISVD_LA_BLAS_TYPE_DEFINE@

#if defined(ISVD_USE_MKL)

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

extern INT isamin_(ISVD_UNKNOWN);
extern INT idamin_(ISVD_UNKNOWN);
extern INT icamin_(ISVD_UNKNOWN);
extern INT izamin_(ISVD_UNKNOWN);

#endif  // DOXYGEN_SHOULD_SKIP_THIS

#if defined(__cplusplus)
}
#endif  // __cplusplus

INT isvd_isAmin( const INT n, const REAL4 *x, const INT incx ) { return isamin_(&n, x, &incx); }
INT isvd_idAmin( const INT n, const REAL8 *x, const INT incx ) { return idamin_(&n, x, &incx); }
INT isvd_icAmin( const INT n, const COMP4 *x, const INT incx ) { return icamin_(&n, x, &incx); }
INT isvd_izAmin( const INT n, const COMP8 *x, const INT incx ) { return izamin_(&n, x, &incx); }

#else  // ISVD_USE_MKL

#define isvd_ixAmin( RTYPE, n, x, incx, abs ) \
  if ( n < 1 || incx <= 0 ) { return -1; } \
  if ( n == 1 ) { return 0; } \
  INT idamin = 0; \
  RTYPE smin = abs(x[0]); \
  for ( INT i = 1, j = incx; i < n; ++i, j += incx ) { \
    if ( abs(x[j]) < smin) { \
      idamin = i; \
      smin = abs(x[j]); \
    } \
  } \
  return idamin;

INT isvd_isAmin( const INT n, const REAL4 *x, const INT incx ) { isvd_ixAmin(REAL4, n, x, incx, fabsf); }
INT isvd_idAmin( const INT n, const REAL8 *x, const INT incx ) { isvd_ixAmin(REAL8, n, x, incx, fabs); }
INT isvd_icAmin( const INT n, const COMP4 *x, const INT incx ) { isvd_ixAmin(REAL4, n, x, incx, cabsf); }
INT isvd_izAmin( const INT n, const COMP8 *x, const INT incx ) { isvd_ixAmin(REAL8, n, x, incx, cabs); }

#endif  // ISVD_USE_MKL

REAL4 isvd_sAmin( const INT n, const REAL4 *x, const INT incx ) { INT i = isvd_isAmin(n, x, incx); return fabsf(x[i]); }
REAL8 isvd_dAmin( const INT n, const REAL8 *x, const INT incx ) { INT i = isvd_idAmin(n, x, incx); return fabs(x[i]); }
COMP4 isvd_cAmin( const INT n, const COMP4 *x, const INT incx ) { INT i = isvd_icAmin(n, x, incx); return cabsf(x[i]); }
COMP8 isvd_zAmin( const INT n, const COMP8 *x, const INT incx ) { INT i = isvd_izAmin(n, x, incx); return cabs(x[i]); }

@ISVD_LA_BLAS_TYPE_UNDEF@
