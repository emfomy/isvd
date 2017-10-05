////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/vml/power_root.h
/// \brief      The VML power and root routines.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef ISVD_LA_VML_POWER_ROOT_H_
#define ISVD_LA_VML_POWER_ROOT_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

@ISVD_TYPE_MACRO_DEFINE@

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_vml_pow_module
/// \brief  Divides elements of one vector by elements of the second vector.
//\{
void isvd_vsDiv( const INT n, const REAL4 *a, const REAL4 *b, REAL4 *y );
void isvd_vdDiv( const INT n, const REAL8 *a, const REAL8 *b, REAL8 *y );
void isvd_vcDiv( const INT n, const COMP4 *a, const COMP4 *b, COMP4 *y );
void isvd_vzDiv( const INT n, const COMP8 *a, const COMP8 *b, COMP8 *y );
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_vml_pow_module
/// \brief  Computes the square root of vector elements.
//\{
void isvd_vsSqrt( const INT n, const REAL4 *a, REAL4 *y );
void isvd_vdSqrt( const INT n, const REAL8 *a, REAL8 *y );
void isvd_vcSqrt( const INT n, const COMP4 *a, COMP4 *y );
void isvd_vzSqrt( const INT n, const COMP8 *a, COMP8 *y );
//\}

@ISVD_TYPE_MACRO_UNDEF@

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_LA_VML_POWER_ROOT_H_
