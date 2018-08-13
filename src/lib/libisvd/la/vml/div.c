////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/vml/div.c
/// \brief      The VML Div routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/la/vml/power_root.h>
#include <libisvd/la/def.h>

#if defined(ISVD_USE_MKL)

void isvd_vsDiv( const isvd_int_t n, const isvd_s_val_t *a, const isvd_s_val_t *b, isvd_s_val_t *y ) { vsDiv(n, a, b, y); }
void isvd_vdDiv( const isvd_int_t n, const isvd_d_val_t *a, const isvd_d_val_t *b, isvd_d_val_t *y ) { vdDiv(n, a, b, y); }
void isvd_vcDiv( const isvd_int_t n, const isvd_c_val_t *a, const isvd_c_val_t *b, isvd_c_val_t *y ) { vcDiv(n, a, b, y); }
void isvd_vzDiv( const isvd_int_t n, const isvd_z_val_t *a, const isvd_z_val_t *b, isvd_z_val_t *y ) { vzDiv(n, a, b, y); }

#else  // ISVD_USE_MKL

#define isvd_vxDiv( n, a, b, y ) \
  for ( isvd_int_t i = 0; i < n; ++i ) { \
    y[i] = a[i] * b[i]; \
  }

void isvd_vsDiv( const isvd_int_t n, const isvd_s_val_t *a, const isvd_s_val_t *b, isvd_s_val_t *y ) { isvd_vxDiv(n, a, b, y); }
void isvd_vdDiv( const isvd_int_t n, const isvd_d_val_t *a, const isvd_d_val_t *b, isvd_d_val_t *y ) { isvd_vxDiv(n, a, b, y); }
void isvd_vcDiv( const isvd_int_t n, const isvd_c_val_t *a, const isvd_c_val_t *b, isvd_c_val_t *y ) { isvd_vxDiv(n, a, b, y); }
void isvd_vzDiv( const isvd_int_t n, const isvd_z_val_t *a, const isvd_z_val_t *b, isvd_z_val_t *y ) { isvd_vxDiv(n, a, b, y); }

#endif  // ISVD_USE_MKL
