////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/gpu/def.h
/// \brief      The GPU definitions.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _LIBISVD_GPU_DEF_H_
#define _LIBISVD_GPU_DEF_H_

#if !defined(ISVD_USE_GPU)
  #error ISVD_USE_GPU must be set to enable GPU support!
#endif

#include <libisvd/def.h>

#if defined(ISVD_USE_ILP64) && !defined(MAGMA_ILP64)
  #define MAGMA_ILP64
#else  // ISVD_USE_ILP64
  #undef MAGMA_ILP64
#endif  // ISVD_USE_ILP64

#include <magma.h>

#endif  // _LIBISVD_GPU_DEF_H_
