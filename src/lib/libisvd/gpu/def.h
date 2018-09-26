////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/gpu/def.h
/// \brief      The GPU definitions.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef LIBISVD_GPU_DEF_H_
#define LIBISVD_GPU_DEF_H_

#if !defined(ISVD_USE_GPU)
  #error ISVD_USE_GPU must be set to enable GPU support!
#endif  // ISVD_USE_GPU

#include <libisvd/def.h>

#if defined(ISVD_USE_ILP64) && !defined(MAGMA_ILP64)
  #define MAGMA_ILP64
#else  // ISVD_USE_ILP64
  #undef MAGMA_ILP64
#endif  // ISVD_USE_ILP64

#include <magma.h>

static const size_t isvd_kBlockSizeGpu = 64;

#define isvd_assert_pass_cuda( condition ) \
  cudaError_t code = condition; \
  if ( code ) fprintf(stderr, "[%s] %s!\n", cudaGetErrorName(code), cudaGetErrorString(code)); \
  isvd_assert_pass(code);

#endif  // LIBISVD_GPU_DEF_H_
