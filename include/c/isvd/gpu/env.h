////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/gpu/env.h
/// \brief      The iSVD environment routines (GPU only).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _ISVD_GPU_ENV_H_
#define _ISVD_GPU_ENV_H_

#include <isvd/def.h>
#include <mpi.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

void isvd_init_gpu( int *argcp, char ***argvp, const MPI_Comm mpi_comm );

void isvd_finalize_gpu( void );

void isvd_printEnvironment_gpu( const MPI_Comm comm );

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_GPU_ENV_H_
