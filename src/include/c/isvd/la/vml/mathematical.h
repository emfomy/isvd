////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/vml/mathematical.h
/// \brief      The VML mathematical routines.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef ISVD_LA_VML_MATHEMATICAL_H_
#define ISVD_LA_VML_MATHEMATICAL_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

@ISVD_TYPE_MACRO_DEFINE@

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_vml_math_module
/// \brief  Subtracts vector elements.
//\{
void isvd_vsSub( const INT n, const REAL4 *a, const REAL4 *b, REAL4 *y );
void isvd_vdSub( const INT n, const REAL8 *a, const REAL8 *b, REAL8 *y );
void isvd_vcSub( const INT n, const COMP4 *a, const COMP4 *b, COMP4 *y );
void isvd_vzSub( const INT n, const COMP8 *a, const COMP8 *b, COMP8 *y );
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_vml_math_module
/// \brief  Multiplies vector elements.
//\{
void isvd_vsMul( const INT n, const REAL4 *a, const REAL4 *b, REAL4 *y );
void isvd_vdMul( const INT n, const REAL8 *a, const REAL8 *b, REAL8 *y );
void isvd_vcMul( const INT n, const COMP4 *a, const COMP4 *b, COMP4 *y );
void isvd_vzMul( const INT n, const COMP8 *a, const COMP8 *b, COMP8 *y );
//\}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_vml_math_module
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

#endif  // ISVD_LA_VML_MATHEMATICAL_H_
