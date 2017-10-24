////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/vml/mul.c
/// \brief      The VML Mul routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/la/vml/mathematical.h>
#include <libisvd/la/def.h>

#if defined(ISVD_USE_MKL)

void isvd_vsMul( const isvd_int_t n, const isvd_s_val_t *a, const isvd_s_val_t *b, isvd_s_val_t *y ) { vsMul(n, a, b, y); }
void isvd_vdMul( const isvd_int_t n, const isvd_d_val_t *a, const isvd_d_val_t *b, isvd_d_val_t *y ) { vdMul(n, a, b, y); }
void isvd_vcMul( const isvd_int_t n, const isvd_c_val_t *a, const isvd_c_val_t *b, isvd_c_val_t *y ) { vcMul(n, a, b, y); }
void isvd_vzMul( const isvd_int_t n, const isvd_z_val_t *a, const isvd_z_val_t *b, isvd_z_val_t *y ) { vzMul(n, a, b, y); }

#else  // ISVD_USE_MKL

#define isvd_vxMul( n, a, b, y ) \
  for ( isvd_int_t i = 0; i < n; ++i ) { \
    y[i] = a[i] * b[i]; \
  }

void isvd_vsMul( const isvd_int_t n, const isvd_s_val_t *a, const isvd_s_val_t *b, isvd_s_val_t *y ) { isvd_vxMul(n, a, b, y); }
void isvd_vdMul( const isvd_int_t n, const isvd_d_val_t *a, const isvd_d_val_t *b, isvd_d_val_t *y ) { isvd_vxMul(n, a, b, y); }
void isvd_vcMul( const isvd_int_t n, const isvd_c_val_t *a, const isvd_c_val_t *b, isvd_c_val_t *y ) { isvd_vxMul(n, a, b, y); }
void isvd_vzMul( const isvd_int_t n, const isvd_z_val_t *a, const isvd_z_val_t *b, isvd_z_val_t *y ) { isvd_vxMul(n, a, b, y); }

#endif  // ISVD_USE_MKL
