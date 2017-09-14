////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/vsl/driver.h
/// \brief      The VSL driver header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef ISVD_LA_VSL_DRIVER_H_
#define ISVD_LA_VSL_DRIVER_H_

#include <isvd/def.h>
#include <isvd/la/vsl/service.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

@ISVD_TYPE_MACRO_DEFINE@

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_vsl_driver_module
/// \brief  Generates normally distributed random numbers in parallel.
//\{
void isvd_vsRngGaussianDriver( const INT seed, const INT nskip, const INT n, REAL4 *r, const REAL4 a, const REAL4 sigma );
void isvd_vdRngGaussianDriver( const INT seed, const INT nskip, const INT n, REAL8 *r, const REAL8 a, const REAL8 sigma );
//\}

@ISVD_TYPE_MACRO_UNDEF@

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_LA_VSL_DRIVER_H_
