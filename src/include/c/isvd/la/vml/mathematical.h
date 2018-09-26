////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/vml/mathematical.h
/// \brief      The VML mathematical routines.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef ISVD_LA_VML_MATHEMATICAL_H_
#define ISVD_LA_VML_MATHEMATICAL_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_vml_math_module
/// \brief  Subtracts vector elements.
//\{
void isvd_vsSub( const isvd_int_t n, const isvd_s_val_t *a, const isvd_s_val_t *b, isvd_s_val_t *y );
void isvd_vdSub( const isvd_int_t n, const isvd_d_val_t *a, const isvd_d_val_t *b, isvd_d_val_t *y );
void isvd_vcSub( const isvd_int_t n, const isvd_c_val_t *a, const isvd_c_val_t *b, isvd_c_val_t *y );
void isvd_vzSub( const isvd_int_t n, const isvd_z_val_t *a, const isvd_z_val_t *b, isvd_z_val_t *y );
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_vml_math_module
/// \brief  Multiplies vector elements.
//\{
void isvd_vsMul( const isvd_int_t n, const isvd_s_val_t *a, const isvd_s_val_t *b, isvd_s_val_t *y );
void isvd_vdMul( const isvd_int_t n, const isvd_d_val_t *a, const isvd_d_val_t *b, isvd_d_val_t *y );
void isvd_vcMul( const isvd_int_t n, const isvd_c_val_t *a, const isvd_c_val_t *b, isvd_c_val_t *y );
void isvd_vzMul( const isvd_int_t n, const isvd_z_val_t *a, const isvd_z_val_t *b, isvd_z_val_t *y );
//\}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_LA_VML_MATHEMATICAL_H_
