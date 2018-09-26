////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/vsl/driver.h
/// \brief      The VSL driver header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef ISVD_LA_VSL_DRIVER_H_
#define ISVD_LA_VSL_DRIVER_H_

#include <isvd/def.h>
#include <isvd/la/vsl/service.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_vsl_driver_module
/// \brief  Generates normally distributed random numbers in parallel.
//\{
void isvd_vsRngGaussianDriver(
    const isvd_int_t seed, const isvd_int_t nskip, const isvd_int_t n, isvd_s_val_t *r, const isvd_s_val_t a,
    const isvd_s_val_t sigma
);
void isvd_vdRngGaussianDriver(
    const isvd_int_t seed, const isvd_int_t nskip, const isvd_int_t n, isvd_d_val_t *r, const isvd_d_val_t a,
    const isvd_d_val_t sigma
);
//\}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_LA_VSL_DRIVER_H_
