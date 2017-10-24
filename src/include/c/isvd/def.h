////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/def.h
/// \brief      The definitions.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef ISVD_DEF_H_
#define ISVD_DEF_H_

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
#if !defined(__STDC_FORMAT_MACROS)
  #define __STDC_FORMAT_MACROS
#endif  // __STDC_FORMAT_MACROS
#endif  // DOXYGEN_SHOULD_SKIP_THIS

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <complex.h>
#include <math.h>
#include <isvd/config.h>

#undef I
#undef imaginary
#undef complex

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
#if !defined(__cplusplus)
  #define ISVD_UNKNOWN
#else  // __cplusplus
  #define ISVD_UNKNOWN ...
#endif  // __cplusplus
#endif  // DOXYGEN_SHOULD_SKIP_THIS

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

/// \ingroup  c_core_module
/// \brief  The type of index. (N = 32/64)
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
#if !defined(ISVD_USE_ILP64)
typedef int32_t isvd_int_t;
#else  // ISVD_USE_ILP64
typedef int64_t isvd_int_t;
#endif  // ISVD_USE_ILP64
#else  // DOXYGEN_SHOULD_SKIP_THIS)
typedef intN_t  isvd_int_t;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

/// \ingroup  c_core_module
/// \brief  The type of unsigned index. (N = 32/64)
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
#if !defined(ISVD_USE_ILP64)
typedef uint32_t isvd_uint_t;
#else  // ISVD_USE_ILP64
typedef uint64_t isvd_uint_t;
#endif  // ISVD_USE_ILP64
#else  // DOXYGEN_SHOULD_SKIP_THIS)
typedef uintN_t  isvd_uint_t;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

/// \ingroup  c_core_module
/// \brief  The type of real single floating point.
typedef float           isvd_s_val_t;

/// \ingroup  c_core_module
/// \brief  The type of real double floating point.
typedef double          isvd_d_val_t;

/// \ingroup  c_core_module
/// \brief  The type of complex single floating point.
typedef _Complex float  isvd_c_val_t;

/// \ingroup  c_core_module
/// \brief  The type of complex double floating point.
typedef _Complex double isvd_z_val_t;

/// \ingroup  c_core_module
/// \brief  The type of MPI index.
typedef int mpi_int_t;

/// \ingroup  c_core_module
/// \brief    The type of OpenMP index.
typedef int omp_int_t;

/// \ingroup  c_core_module
/// \brief  The MPI communicator type.
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
typedef int isvd_MpiComm;
#else  // DOXYGEN_SHOULD_SKIP_THIS)
typedef MPI_Comm isvd_MpiComm;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_DEF_H_
