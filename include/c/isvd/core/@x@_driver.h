////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/core/@x@_driver.h
/// \brief      The @xname@ precision drivers.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef ISVD_CORE_@X@_DRIVER_H_
#define ISVD_CORE_@X@_DRIVER_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

// General iSVD driver
void isvd_@x@Isvd(
    const char *alg_s, const char *alg_o, const char *alg_i, const char *alg_p,
    const isvd_int_t m, const isvd_int_t n, const isvd_int_t k, const isvd_int_t p, const isvd_int_t N,
    const @xtype@ *argv[4], const isvd_int_t argc[4], @xtype@ *retv[4], const isvd_int_t retc[4],
    double time[4], FILE *stream,
    const char dista, const char ordera, const @xtype@ *a, const isvd_int_t lda,
    @xtype@ *s, @xtype@ *ut, const isvd_int_t ldut, @xtype@ *vt, const isvd_int_t ldvt,
    const isvd_int_t seed, const mpi_int_t ut_root, const mpi_int_t vt_root,
    const mpi_int_t mpi_root, const isvd_MpiComm mpi_comm
);

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_CORE_@X@_DRIVER_H_
