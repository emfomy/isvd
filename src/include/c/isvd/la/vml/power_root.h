////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/vml/power_root.h
/// \brief      The VML power and root routines.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef ISVD_LA_VML_POWER_ROOT_H_
#define ISVD_LA_VML_POWER_ROOT_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_vml_pow_module
/// \brief  Divides elements of one vector by elements of the second vector.
//\{
void isvd_vsDiv( const isvd_int_t n, const isvd_s_val_t *a, const isvd_s_val_t *b, isvd_s_val_t *y );
void isvd_vdDiv( const isvd_int_t n, const isvd_d_val_t *a, const isvd_d_val_t *b, isvd_d_val_t *y );
void isvd_vcDiv( const isvd_int_t n, const isvd_c_val_t *a, const isvd_c_val_t *b, isvd_c_val_t *y );
void isvd_vzDiv( const isvd_int_t n, const isvd_z_val_t *a, const isvd_z_val_t *b, isvd_z_val_t *y );
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_vml_pow_module
/// \brief  Computes the square root of vector elements.
//\{
void isvd_vsSqrt( const isvd_int_t n, const isvd_s_val_t *a, isvd_s_val_t *y );
void isvd_vdSqrt( const isvd_int_t n, const isvd_d_val_t *a, isvd_d_val_t *y );
void isvd_vcSqrt( const isvd_int_t n, const isvd_c_val_t *a, isvd_c_val_t *y );
void isvd_vzSqrt( const isvd_int_t n, const isvd_z_val_t *a, isvd_z_val_t *y );
//\}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_LA_VML_POWER_ROOT_H_
