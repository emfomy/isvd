////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/vsl/distribution.h
/// \brief      The VSL distribution header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef ISVD_LA_VSL_DISTRIBUTION_H_
#define ISVD_LA_VSL_DISTRIBUTION_H_

#include <isvd/def.h>
#include <isvd/la/vsl/service.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

@ISVD_LA_BLAS_TYPE_DEFINE@

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_vsl_distribution_module
/// \brief  Generates normally distributed random numbers.
//\{
void isvd_vsRngGaussian( isvd_VSLStreamStatePtr stream, const INT n, REAL4 *r, const REAL4 a, const REAL4 sigma );
void isvd_vdRngGaussian( isvd_VSLStreamStatePtr stream, const INT n, REAL8 *r, const REAL8 a, const REAL8 sigma );
//\}

@ISVD_LA_BLAS_TYPE_UNDEF@

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_LA_VSL_DISTRIBUTION_H_
