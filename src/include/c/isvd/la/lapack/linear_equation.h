////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/lapack/linear_equation.h
/// \brief      The LAPACK linear equation header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef ISVD_LA_LAPACK_LINEAR_EQUATION_H_
#define ISVD_LA_LAPACK_LINEAR_EQUATION_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

@ISVD_TYPE_MACRO_DEFINE@

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_lapack_le_module
/// \brief  Computes the inverse of a square matrix using LU factorization.
//\{
void isvd_sGeinv( const INT n, REAL4 *a, const INT lda );
void isvd_dGeinv( const INT n, REAL8 *a, const INT lda );
void isvd_cGeinv( const INT n, COMP4 *a, const INT lda );
void isvd_zGeinv( const INT n, COMP8 *a, const INT lda );
//\}

@ISVD_TYPE_MACRO_UNDEF@

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_LA_LAPACK_LINEAR_EQUATION_H_
