////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/la/blas/iamax.c
/// \brief      The BLAS-1 iAmax routine.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/la/blas/blas1.h>
#include <libisvd/la/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

extern isvd_int_t isamax_(ISVD_UNKNOWN);
extern isvd_int_t idamax_(ISVD_UNKNOWN);
extern isvd_int_t icamax_(ISVD_UNKNOWN);
extern isvd_int_t izamax_(ISVD_UNKNOWN);

#endif  // DOXYGEN_SHOULD_SKIP_THIS

#if defined(__cplusplus)
}
#endif  // __cplusplus

isvd_int_t isvd_isAmax( const isvd_int_t n, const isvd_s_val_t *x, const isvd_int_t incx ) { return isamax_(&n, x, &incx); }
isvd_int_t isvd_idAmax( const isvd_int_t n, const isvd_d_val_t *x, const isvd_int_t incx ) { return idamax_(&n, x, &incx); }
isvd_int_t isvd_icAmax( const isvd_int_t n, const isvd_c_val_t *x, const isvd_int_t incx ) { return icamax_(&n, x, &incx); }
isvd_int_t isvd_izAmax( const isvd_int_t n, const isvd_z_val_t *x, const isvd_int_t incx ) { return izamax_(&n, x, &incx); }

isvd_s_val_t isvd_sAmax( const isvd_int_t n, const isvd_s_val_t *x, const isvd_int_t incx ) {
  isvd_int_t i = isvd_isAmax(n, x, incx); return fabsf(x[i]);
}
isvd_d_val_t isvd_dAmax( const isvd_int_t n, const isvd_d_val_t *x, const isvd_int_t incx ) {
  isvd_int_t i = isvd_idAmax(n, x, incx); return fabs(x[i]);
}
isvd_c_val_t isvd_cAmax( const isvd_int_t n, const isvd_c_val_t *x, const isvd_int_t incx ) {
  isvd_int_t i = isvd_icAmax(n, x, incx); return cabsf(x[i]);
}
isvd_z_val_t isvd_zAmax( const isvd_int_t n, const isvd_z_val_t *x, const isvd_int_t incx ) {
  isvd_int_t i = isvd_izAmax(n, x, incx); return cabs(x[i]);
}
