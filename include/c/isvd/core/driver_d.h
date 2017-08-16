////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/core/driver_d.h
/// @brief   The double precision drivers.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_CORE_DRIVER_D_H_
#define _ISVD_CORE_DRIVER_D_H_

#include <isvd/core/def.h>
#include <isvd/core/param.h>
#include <isvd/core/stage_d.h>

// General iSVD driver
void isvd_dIsvd(
    const char *algs, const char *algo, const char *algi, const char *algp,
    const isvd_int_t m, const isvd_int_t n, const isvd_int_t k, const isvd_int_t p, const isvd_int_t N,
    const char dista, const char ordera, const double *a, const isvd_int_t lda,
    double *s, double *ut, const isvd_int_t ldut, double *vt, const isvd_int_t ldvt,
    const isvd_int_t seed, const mpi_int_t seed_root, const mpi_int_t ut_root, const mpi_int_t vt_root,
    const MPI_Comm mpi_comm
);

// Symmetric iSVD driver
void isvd_dIeig(
    const char *algs, const char *algo, const char *algi, const char *algp,
    const isvd_int_t m, const isvd_int_t k, const isvd_int_t p, const isvd_int_t N,
    const char dista, const char ordera, const double *a, const isvd_int_t lda,
    double *s, double *ut, const isvd_int_t ldut,
    const isvd_int_t seed, const mpi_int_t seed_root, const mpi_int_t ut_root,
    const MPI_Comm mpi_comm
);

#endif  // _ISVD_CORE_DRIVER_D_H_
