////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/vml/sub.c
/// \brief      The VML Sub routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/la/vml/mathematical.h>
#include <libisvd/la/def.h>

#if defined(ISVD_USE_MKL)

void isvd_vsSub( const isvd_int_t n, const isvd_s_val_t *a, const isvd_s_val_t *b, isvd_s_val_t *y ) { vsSub(n, a, b, y); }
void isvd_vdSub( const isvd_int_t n, const isvd_d_val_t *a, const isvd_d_val_t *b, isvd_d_val_t *y ) { vdSub(n, a, b, y); }
void isvd_vcSub( const isvd_int_t n, const isvd_c_val_t *a, const isvd_c_val_t *b, isvd_c_val_t *y ) { vcSub(n, a, b, y); }
void isvd_vzSub( const isvd_int_t n, const isvd_z_val_t *a, const isvd_z_val_t *b, isvd_z_val_t *y ) { vzSub(n, a, b, y); }

#else  // ISVD_USE_MKL

#define isvd_vxSub( n, a, b, y ) \
  for ( isvd_int_t i = 0; i < n; ++i ) { \
    y[i] = a[i] - b[i]; \
  }

void isvd_vsSub( const isvd_int_t n, const isvd_s_val_t *a, const isvd_s_val_t *b, isvd_s_val_t *y ) { isvd_vxSub(n, a, b, y); }
void isvd_vdSub( const isvd_int_t n, const isvd_d_val_t *a, const isvd_d_val_t *b, isvd_d_val_t *y ) { isvd_vxSub(n, a, b, y); }
void isvd_vcSub( const isvd_int_t n, const isvd_c_val_t *a, const isvd_c_val_t *b, isvd_c_val_t *y ) { isvd_vxSub(n, a, b, y); }
void isvd_vzSub( const isvd_int_t n, const isvd_z_val_t *a, const isvd_z_val_t *b, isvd_z_val_t *y ) { isvd_vxSub(n, a, b, y); }

#endif  // ISVD_USE_MKL
