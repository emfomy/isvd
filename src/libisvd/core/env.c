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
  mpi_int_t mpi_size = isvd_getMpiSize(mpi_comm), omp_size;
  ISVD_OMP_PARALLEL
  {
    omp_size = isvd_getOmpSize();
  }

  printf("iSVD %s, %lu-bit isvd_int_t, %lu-bit pointer\n", ISVD_VERSION, sizeof(isvd_int_t) * 8, sizeof(void*) * 8);
  printf("%d MPI nodes, %d OpenMP threads per node\n\n", mpi_size, omp_size);
}
