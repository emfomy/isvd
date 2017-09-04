////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/gpu/env.c
/// \brief      The iSVD environment routines with GPU support.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/gpu/env.h>
#include <libisvd/gpu/def.h>
#include <libisvd/util/mpi.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_gpu_module
/// Initializes the iSVD environment with GPU support.
///
/// \note  This routines initializes the MAGMA environment.
///
void isvd_init_gpu( int *argcp, char ***argvp, const MPI_Comm mpi_comm ) {
  ISVD_UNUSED(argcp);
  ISVD_UNUSED(argvp);
  const isvd_int_t mpi_rank = isvd_getMpiRank(mpi_comm);
  int count;
  cudaGetDeviceCount(&count);
  magma_init();
  magma_setdevice(mpi_rank % count);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_gpi_module
/// Finalizes the iSVD environment with GPU support.
///
/// \note  This routines initializes the MAGMA environment.
///
void isvd_finalize_gpu( void ) {
  magma_finalize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_gpu_module
/// Displays the iSVD environment with GPU support.
///
/// \note  This routines displays the MAGMA environment.
///
void isvd_printEnvironment_gpu( const MPI_Comm mpi_comm ) {
  ISVD_UNUSED(mpi_comm);
  magma_print_environment();
  printf("\n");
}
