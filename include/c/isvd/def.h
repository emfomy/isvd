////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/def.h
/// \brief      The definitions.
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

#if !defined(__cplusplus)
  #define ISVD_UNKNOWN
#else  // __cplusplus
  #define ISVD_UNKNOWN ...
#endif  // __cplusplus

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

/// \ingroup  c_core_module
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

/// \ingroup  c_core_module
/// The type of MPI index.
typedef int mpi_int_t;

/// \ingroup  c_core_module
/// The type of OpenMP index.
typedef int omp_int_t;

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_DEF_H_
