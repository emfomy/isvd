////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/gpu/env.h
/// \brief      The iSVD environment routines (GPU only).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef ISVD_GPU_ENV_H_
#define ISVD_GPU_ENV_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

extern size_t isvd_gpu_memory_limit;

void isvd_Init_gpu( int *argcp, char ***argvp, const isvd_MpiComm mpi_comm );

void isvd_Finalize_gpu( void );

void isvd_PrintEnvironment_gpu( const isvd_MpiComm comm );

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_GPU_ENV_H_
