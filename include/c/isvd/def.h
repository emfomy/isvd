////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/def.h
/// @brief   The iSVD definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_DEF_H_
#define _ISVD_DEF_H_

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <complex.h>
#include <math.h>
#include <mpi.h>
#include <isvd/config.h>

#define ISVD_UNUSED( x ) (void)(x)

/// @ingroup  core_module
/// The type of index.
#ifndef ISVD_USE_ILP64
typedef int32_t index_t;
#else  // ISVD_USE_ILP64
typedef int64_t index_t;
#endif  // ISVD_USE_ILP64

typedef int mpi_int_t;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#ifdef ISVD_USE_MKL
#define MKL_INT index_t
#define MKL_Complex8  float complex
#define MKL_Complex16 double complex
#endif  // ISVD_USE_MKL
#endif  // DOXYGEN_SHOULD_SKIP_THIS

#endif  // _ISVD_DEF_H_
