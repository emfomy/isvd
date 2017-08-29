////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/def.h
/// \brief      The iSVD definitions.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _ISVD_DEF_H_
#define _ISVD_DEF_H_

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <complex.h>
#include <math.h>
#include <isvd/config.h>

#include <mpi.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

/// \ingroup  core_module
/// The type of index.
//\{
#if !defined(ISVD_USE_ILP64)
typedef int32_t  isvd_int_t;
typedef uint32_t isvd_uint_t;
#else  // ISVD_USE_ILP64
typedef int64_t  isvd_int_t;
typedef uint64_t isvd_uint_t;
#endif  // ISVD_USE_ILP64
//\}

/// \ingroup  core_module
/// The type of MPI index.
typedef int mpi_int_t;

/// \ingroup  core_module
/// The type of OpenMP index.
typedef int omp_int_t;

typedef int MPI_Comm;

void isvd_printEnvironment( const MPI_Comm comm, const mpi_int_t mpi_root );

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_DEF_H_
