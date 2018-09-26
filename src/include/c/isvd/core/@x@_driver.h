////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/core/@x@_driver.h
/// \brief      The @xname@ precision drivers.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef ISVD_CORE_@X@_DRIVER_H_
#define ISVD_CORE_@X@_DRIVER_H_

#include <isvd/def.h>
#include <isvd/core/param.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

// General iSVD driver
void isvd_@x@Isvd(
    const isvd_Param param,
    const char *alg_s, const char *alg_o, const char *alg_i, const char *alg_p,
    const @xtype_____@ *argv[4], const isvd_int_t argc[4], @xtype_____@ *retv[4], const isvd_int_t retc[4],
    double time[4], FILE *stream,
    const char dista, const char ordera, const @xtype_____@ *a, const isvd_int_t lda,
    @xtype_____@ *s, @xtype_____@ *ut, const isvd_int_t ldut, @xtype_____@ *vt, const isvd_int_t ldvt,
    const isvd_int_t seed, const mpi_int_t ut_root, const mpi_int_t vt_root
);

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_CORE_@X@_DRIVER_H_
