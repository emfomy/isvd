////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/core/env.c
/// \brief      The iSVD environment routines.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/core/env.h>
#include <libisvd/def.h>
#include <libisvd/util/mpi.h>
#include <libisvd/util/omp.h>

#if defined(ISVD_USE_GPU)
#include <isvd/gpu/env.h>
#endif  // ISVD_USE_GPU

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_module
/// Initializes the iSVD environment.
///
/// \note  This routines initializes the MPI and MAGMA environments.
///
void isvd_init( int *argcp, char ***argvp, const MPI_Comm mpi_comm ) {
  isvd_init_cpu(argcp, argvp, mpi_comm);
#if defined(MCNLA_USE_GPU)
  isvd_init_gpu(argcp, argvp, mpi_comm);
#endif  // MCNLA_USE_GPU
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_module
/// Initializes the iSVD environment without GPU support.
///
/// \note  This routines initializes the MPI environment.
///
void isvd_init_cpu( int *argcp, char ***argvp, const MPI_Comm mpi_comm ) {
  ISVD_UNUSED(mpi_comm);
  MPI_Init(argcp, argvp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_module
/// Finalizes the iSVD environment.
///
/// \note  This routines initializes the MPI and MAGMA environments.
///
void isvd_finalize() {
  isvd_finalize_cpu();
#if defined(MCNLA_USE_GPU)
  isvd_finalize_gpu();
#endif  // MCNLA_USE_GPU
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_module
/// Finalizes the iSVD environment without GPU support.
///
/// \note  This routines initializes the MPI environment.
///
void isvd_finalize_cpu( void ) {
  MPI_Finalize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_module
/// Displays the iSVD environment.
///
/// \note  This routines displays the MPI and MAGMA environments.
///
void isvd_printEnvironment( const MPI_Comm mpi_comm ) {
  isvd_printEnvironment_cpu(mpi_comm);
#if defined(ISVD_USE_GPU)
  isvd_printEnvironment_gpu(mpi_comm);
#endif  // ISVD_USE_GPU
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_module
/// Displays the iSVD environment without GPU support.
///
/// \note  This routines displays the MPI environment.
///
void isvd_printEnvironment_cpu( const MPI_Comm mpi_comm ) {
  const mpi_int_t mpi_size = isvd_getMpiSize(mpi_comm);
  const omp_int_t omp_size = isvd_getOmpSize();

  printf("%d nodes, %d threads per node\n", mpi_size, omp_size);
  printf("%lu-bit integer\n\n", sizeof(isvd_int_t) * 8);
}
