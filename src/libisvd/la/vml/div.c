////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/la/vml/div.c
/// \brief      The VML Div routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/la/vml/power_root.h>
#include <libisvd/la/def.h>

@ISVD_LA_BLAS_TYPE_DEFINE@

#if defined(ISVD_USE_MKL)

void isvd_vsDiv( const INT n, const REAL4 *a, const REAL4 *b, REAL4 *y ) { vsDiv(n, a, b, y); }
void isvd_vdDiv( const INT n, const REAL8 *a, const REAL8 *b, REAL8 *y ) { vdDiv(n, a, b, y); }
void isvd_vcDiv( const INT n, const COMP4 *a, const COMP4 *b, COMP4 *y ) { vcDiv(n, a, b, y); }
void isvd_vzDiv( const INT n, const COMP8 *a, const COMP8 *b, COMP8 *y ) { vzDiv(n, a, b, y); }

#else  // ISVD_USE_MKL

#define isvd_vxDiv( n, a, b, y ) \
  for ( isvd_int_t i = 0; i < n; ++i ) { \
    y[i] = a[i] * b[i]; \
  }

void isvd_vsDiv( const INT n, const REAL4 *a, const REAL4 *b, REAL4 *y ) { isvd_vxDiv(n, a, b, y); }
void isvd_vdDiv( const INT n, const REAL8 *a, const REAL8 *b, REAL8 *y ) { isvd_vxDiv(n, a, b, y); }
void isvd_vcDiv( const INT n, const COMP4 *a, const COMP4 *b, COMP4 *y ) { isvd_vxDiv(n, a, b, y); }
void isvd_vzDiv( const INT n, const COMP8 *a, const COMP8 *b, COMP8 *y ) { isvd_vxDiv(n, a, b, y); }

#endif  // ISVD_USE_MKL

@ISVD_LA_BLAS_TYPE_UNDEF@
