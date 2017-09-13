////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/gpu/env.h
/// \brief      The iSVD environment routines (GPU only).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef ISVD_GPU_ENV_H_
#define ISVD_GPU_ENV_H_

#include <isvd/def.h>
#include <mpi.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

extern size_t isvd_gpu_memory_limit;

void isvd_init_gpu( int *argcp, char ***argvp, const isvd_MpiComm mpi_comm );

void isvd_finalize_gpu( void );

void isvd_printEnvironment_gpu( const isvd_MpiComm comm );

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_GPU_ENV_H_
