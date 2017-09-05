////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/core/env.c
/// \brief      The iSVD environment routines (CPU only).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/core/env.h>
#include <libisvd/def.h>
#include <libisvd/util/mpi.h>
#include <libisvd/util/omp.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_module
/// Initializes the iSVD environment (CPU only).
///
/// \note  This routines initializes the MPI environment.
///
void isvd_init_cpu( int *argcp, char ***argvp, const MPI_Comm mpi_comm ) {
  ISVD_UNUSED(mpi_comm);
  MPI_Init(argcp, argvp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_module
/// Finalizes the iSVD environment (CPU only).
///
/// \note  This routines initializes the MPI environment.
///
void isvd_finalize_cpu( void ) {
  MPI_Finalize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_module
/// Displays the iSVD environment (CPU only).
///
/// \note  This routines displays the MPI environment.
///
void isvd_printEnvironment_cpu( const MPI_Comm mpi_comm ) {
  const mpi_int_t mpi_size = isvd_getMpiSize(mpi_comm);
  const omp_int_t omp_size = isvd_getOmpSize();

  printf("%d nodes, %d threads per node\n", mpi_size, omp_size);
  printf("%lu-bit integer\n\n", sizeof(isvd_int_t) * 8);
}
