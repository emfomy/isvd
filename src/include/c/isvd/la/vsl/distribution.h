////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/vsl/distribution.h
/// \brief      The VSL distribution header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef ISVD_LA_VSL_DISTRIBUTION_H_
#define ISVD_LA_VSL_DISTRIBUTION_H_

#include <isvd/def.h>
#include <isvd/la/vsl/service.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_vsl_distribution_module
/// \brief  Generates normally distributed random numbers.
//\{
void isvd_vsRngGaussian(
    isvd_VSLStreamStatePtr stream, const isvd_int_t n, isvd_s_val_t *r, const isvd_s_val_t a, const isvd_s_val_t sigma
);
void isvd_vdRngGaussian(
    isvd_VSLStreamStatePtr stream, const isvd_int_t n, isvd_d_val_t *r, const isvd_d_val_t a, const isvd_d_val_t sigma
);
//\}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_LA_VSL_DISTRIBUTION_H_
