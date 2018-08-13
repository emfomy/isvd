////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/vml/sqrt.c
/// \brief      The VML Sqrt routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/la/vml/power_root.h>
#include <libisvd/la/def.h>

#if defined(ISVD_USE_MKL)

void isvd_vsSqrt( const isvd_int_t n, const isvd_s_val_t *a, isvd_s_val_t *y ) { vsSqrt(n, a, y); }
void isvd_vdSqrt( const isvd_int_t n, const isvd_d_val_t *a, isvd_d_val_t *y ) { vdSqrt(n, a, y); }
void isvd_vcSqrt( const isvd_int_t n, const isvd_c_val_t *a, isvd_c_val_t *y ) { vcSqrt(n, a, y); }
void isvd_vzSqrt( const isvd_int_t n, const isvd_z_val_t *a, isvd_z_val_t *y ) { vzSqrt(n, a, y); }

#else  // ISVD_USE_MKL

#define isvd_xSqrt( n, a, y, sqrt ) \
  for ( isvd_int_t i = 0; i < n; ++i ) { \
    y[i] = sqrt(a[i]); \
  }

void isvd_vsSqrt( const isvd_int_t n, const isvd_s_val_t *a, isvd_s_val_t *y ) { isvd_xSqrt(n, a, y, sqrtf);  }
void isvd_vdSqrt( const isvd_int_t n, const isvd_d_val_t *a, isvd_d_val_t *y ) { isvd_xSqrt(n, a, y, sqrt);   }
void isvd_vcSqrt( const isvd_int_t n, const isvd_c_val_t *a, isvd_c_val_t *y ) { isvd_xSqrt(n, a, y, csqrtf); }
void isvd_vzSqrt( const isvd_int_t n, const isvd_z_val_t *a, isvd_z_val_t *y ) { isvd_xSqrt(n, a, y, csqrt);  }

#endif  // ISVD_USE_MKL
