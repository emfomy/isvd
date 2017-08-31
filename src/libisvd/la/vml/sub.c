////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/la/vml/sub.c
/// \brief      The VML SUB routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/la/vml/mathematical.h>
#include <libisvd/def.h>

@ISVD_LA_BLAS_TYPE_DEFINE@

#if defined(ISVD_USE_MKL)

void isvd_vsSub( const INT n, const REAL4 *a, const REAL4 *b, REAL4 *y ) { vsSub(n, a, b, y); }
void isvd_vdSub( const INT n, const REAL8 *a, const REAL8 *b, REAL8 *y ) { vdSub(n, a, b, y); }
void isvd_vcSub( const INT n, const COMP4 *a, const COMP4 *b, COMP4 *y ) { vcSub(n, a, b, y); }
void isvd_vzSub( const INT n, const COMP8 *a, const COMP8 *b, COMP8 *y ) { vzSub(n, a, b, y); }

#else  // ISVD_USE_MKL

#define isvd_vxSub( n, a, b, y ) \
  for ( isvd_int_t i = 0; i < n; ++i ) { \
    y[i] = a[i] - b[i]; \
  }

void isvd_vsSub( const INT n, const REAL4 *a, const REAL4 *b, REAL4 *y ) { isvd_vxSub(n, a, b, y); }
void isvd_vdSub( const INT n, const REAL8 *a, const REAL8 *b, REAL8 *y ) { isvd_vxSub(n, a, b, y); }
void isvd_vcSub( const INT n, const COMP4 *a, const COMP4 *b, COMP4 *y ) { isvd_vxSub(n, a, b, y); }
void isvd_vzSub( const INT n, const COMP8 *a, const COMP8 *b, COMP8 *y ) { isvd_vxSub(n, a, b, y); }

#endif  // ISVD_USE_MKL

@ISVD_LA_BLAS_TYPE_UNDEF@
