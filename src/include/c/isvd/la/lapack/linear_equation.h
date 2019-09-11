////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/lapack/linear_equation.h
/// \brief      The LAPACK linear equation header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef ISVD_LA_LAPACK_LINEAR_EQUATION_H_
#define ISVD_LA_LAPACK_LINEAR_EQUATION_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_le_module
/// \brief  Computes the inverse of a square matrix using LU factorization.
//\{
void isvd_sGeinv( const isvd_int_t n, isvd_s_val_t *a, const isvd_int_t lda );
void isvd_dGeinv( const isvd_int_t n, isvd_d_val_t *a, const isvd_int_t lda );
void isvd_cGeinv( const isvd_int_t n, isvd_c_val_t *a, const isvd_int_t lda );
void isvd_zGeinv( const isvd_int_t n, isvd_z_val_t *a, const isvd_int_t lda );
//\}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_LA_LAPACK_LINEAR_EQUATION_H_
