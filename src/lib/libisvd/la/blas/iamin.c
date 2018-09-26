////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/blas/iamin.c
/// \brief      The BLAS-1 iAmin routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/la/blas/blas1.h>
#include <libisvd/la/def.h>

#if defined(ISVD_USE_MKL)

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

extern isvd_int_t isamin_(ISVD_UNKNOWN);
extern isvd_int_t idamin_(ISVD_UNKNOWN);
extern isvd_int_t icamin_(ISVD_UNKNOWN);
extern isvd_int_t izamin_(ISVD_UNKNOWN);

#endif  // DOXYGEN_SHOULD_SKIP_THIS

#if defined(__cplusplus)
}
#endif  // __cplusplus

isvd_int_t isvd_isAmin( const isvd_int_t n, const isvd_s_val_t *x, const isvd_int_t incx ) { return isamin_(&n, x, &incx); }
isvd_int_t isvd_idAmin( const isvd_int_t n, const isvd_d_val_t *x, const isvd_int_t incx ) { return idamin_(&n, x, &incx); }
isvd_int_t isvd_icAmin( const isvd_int_t n, const isvd_c_val_t *x, const isvd_int_t incx ) { return icamin_(&n, x, &incx); }
isvd_int_t isvd_izAmin( const isvd_int_t n, const isvd_z_val_t *x, const isvd_int_t incx ) { return izamin_(&n, x, &incx); }

#else  // ISVD_USE_MKL

#define isvd_ixAmin( RTYPE, n, x, incx, abs ) \
  if ( n < 1 || incx <= 0 ) { return -1; } \
  if ( n == 1 ) { return 0; } \
  isvd_int_t idamin = 0; \
  RTYPE smin = abs(x[0]); \
  for ( isvd_int_t i = 1, j = incx; i < n; ++i, j += incx ) { \
    if ( abs(x[j]) < smin) { \
      idamin = i; \
      smin = abs(x[j]); \
    } \
  } \
  return idamin;

isvd_int_t isvd_isAmin( const isvd_int_t n, const isvd_s_val_t *x, const isvd_int_t incx ) {
  isvd_ixAmin(isvd_s_val_t, n, x, incx, fabsf);
}
isvd_int_t isvd_idAmin( const isvd_int_t n, const isvd_d_val_t *x, const isvd_int_t incx ) {
  isvd_ixAmin(isvd_d_val_t, n, x, incx, fabs);
}
isvd_int_t isvd_icAmin( const isvd_int_t n, const isvd_c_val_t *x, const isvd_int_t incx ) {
  isvd_ixAmin(isvd_s_val_t, n, x, incx, cabsf);
}
isvd_int_t isvd_izAmin( const isvd_int_t n, const isvd_z_val_t *x, const isvd_int_t incx ) {
  isvd_ixAmin(isvd_d_val_t, n, x, incx, cabs);
}

#endif  // ISVD_USE_MKL

isvd_s_val_t isvd_sAmin( const isvd_int_t n, const isvd_s_val_t *x, const isvd_int_t incx ) {
  isvd_int_t i = isvd_isAmin(n, x, incx); return fabsf(x[i]);
}
isvd_d_val_t isvd_dAmin( const isvd_int_t n, const isvd_d_val_t *x, const isvd_int_t incx ) {
  isvd_int_t i = isvd_idAmin(n, x, incx); return fabs(x[i]);
}
isvd_c_val_t isvd_cAmin( const isvd_int_t n, const isvd_c_val_t *x, const isvd_int_t incx ) {
  isvd_int_t i = isvd_icAmin(n, x, incx); return cabsf(x[i]);
}
isvd_z_val_t isvd_zAmin( const isvd_int_t n, const isvd_z_val_t *x, const isvd_int_t incx ) {
  isvd_int_t i = isvd_izAmin(n, x, incx); return cabs(x[i]);
}
