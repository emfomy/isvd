////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/la/vml/mul.c
/// \brief      The VML Mul routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/la/vml/mathematical.h>
#include <libisvd/la/def.h>

@ISVD_LA_BLAS_TYPE_DEFINE@

#if defined(ISVD_USE_MKL)

void isvd_vsMul( const INT n, const REAL4 *a, const REAL4 *b, REAL4 *y ) { vsMul(n, a, b, y); }
void isvd_vdMul( const INT n, const REAL8 *a, const REAL8 *b, REAL8 *y ) { vdMul(n, a, b, y); }
void isvd_vcMul( const INT n, const COMP4 *a, const COMP4 *b, COMP4 *y ) { vcMul(n, a, b, y); }
void isvd_vzMul( const INT n, const COMP8 *a, const COMP8 *b, COMP8 *y ) { vzMul(n, a, b, y); }

#else  // ISVD_USE_MKL

#define isvd_vxMul( n, a, b, y ) \
  for ( isvd_int_t i = 0; i < n; ++i ) { \
    y[i] = a[i] * b[i]; \
  }

void isvd_vsMul( const INT n, const REAL4 *a, const REAL4 *b, REAL4 *y ) { isvd_vxMul(n, a, b, y); }
void isvd_vdMul( const INT n, const REAL8 *a, const REAL8 *b, REAL8 *y ) { isvd_vxMul(n, a, b, y); }
void isvd_vcMul( const INT n, const COMP4 *a, const COMP4 *b, COMP4 *y ) { isvd_vxMul(n, a, b, y); }
void isvd_vzMul( const INT n, const COMP8 *a, const COMP8 *b, COMP8 *y ) { isvd_vxMul(n, a, b, y); }

#endif  // ISVD_USE_MKL

@ISVD_LA_BLAS_TYPE_UNDEF@
