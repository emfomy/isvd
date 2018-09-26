////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/gpu/env.c
/// \brief      The iSVD environment routines (GPU only).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/gpu/env.h>
#include <libisvd/gpu/def.h>
#include <cuda.h>
#include <isvd/util/mpi.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_gpu_module
/// The GPU memory limit.
///
size_t isvd_gpu_memory_limit = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_gpu_module
/// Initializes the iSVD environment (GPU only).
///
/// \note  This routines initializes the MAGMA environment.
///
void isvd_Init_gpu( int *argcp, char ***argvp, const isvd_MpiComm mpi_comm ) {
  ISVD_UNUSED(argcp);
  ISVD_UNUSED(argvp);
  const isvd_int_t mpi_rank = isvd_getMpiRank(mpi_comm);
  int count = 0;
  isvd_assert_pass_cuda(cudaGetDeviceCount(&count));
  isvd_assert_ne(count, 0);
  magma_init();
  magma_setdevice(mpi_rank % count);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_gpi_module
/// Finalizes the iSVD environment (GPU only).
///
/// \note  This routines initializes the MAGMA environment.
///
void isvd_Finalize_gpu( void ) {
  magma_finalize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_gpu_module
/// Displays the iSVD environment (GPU only).
///
/// \note  This routines displays the MAGMA environment.
///
void isvd_PrintEnvironment_gpu( const isvd_MpiComm mpi_comm ) {
  ISVD_UNUSED(mpi_comm);
  magma_print_environment();
  printf("\n");
}
