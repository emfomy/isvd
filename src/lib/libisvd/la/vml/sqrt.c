////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/vml/sqrt.c
/// \brief      The VML Sqrt routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/la/vml/mathematical.h>
#include <libisvd/la/def.h>

@ISVD_LA_BLAS_TYPE_DEFINE@

#if defined(ISVD_USE_MKL)

void isvd_vsSqrt( const INT n, const REAL4 *a, REAL4 *y ) { vsSqrt(n, a, y); }
void isvd_vdSqrt( const INT n, const REAL8 *a, REAL8 *y ) { vdSqrt(n, a, y); }
void isvd_vcSqrt( const INT n, const COMP4 *a, COMP4 *y ) { vcSqrt(n, a, y); }
void isvd_vzSqrt( const INT n, const COMP8 *a, COMP8 *y ) { vzSqrt(n, a, y); }

#else  // ISVD_USE_MKL

#define isvd_xSqrt( n, a, y, sqrt ) \
  for ( isvd_int_t i = 0; i < n; ++i ) { \
    y[i] = sqrt(a[i]); \
  }

void isvd_vsSqrt( const INT n, const REAL4 *a, REAL4 *y ) { isvd_xSqrt(n, a, y, sqrtf);  }
void isvd_vdSqrt( const INT n, const REAL8 *a, REAL8 *y ) { isvd_xSqrt(n, a, y, sqrt);   }
void isvd_vcSqrt( const INT n, const COMP4 *a, COMP4 *y ) { isvd_xSqrt(n, a, y, csqrtf); }
void isvd_vzSqrt( const INT n, const COMP8 *a, COMP8 *y ) { isvd_xSqrt(n, a, y, csqrt);  }

#endif  // ISVD_USE_MKL

@ISVD_LA_BLAS_TYPE_UNDEF@
