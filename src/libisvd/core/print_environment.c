////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/print_environment.c
/// \brief      Display the iSVD environment.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/core/print_environment.h>
#include <libisvd/def.h>
#include <libisvd/util/mpi.h>
#include <libisvd/util/omp.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_module
/// Display the iSVD environment.
///
void isvd_printEnvironment(
    const MPI_Comm  mpi_comm,
    const mpi_int_t mpi_root
) {
  const mpi_int_t mpi_size = isvd_getMpiSize(mpi_comm);
  const mpi_int_t mpi_rank = isvd_getMpiRank(mpi_comm);
  const omp_int_t omp_size = isvd_getOmpSize();

  if ( mpi_rank == mpi_root ) {
    printf("iSVD " ISVD_VERSION " C test\n");
    printf("%d nodes, %d threads per node\n", mpi_size, omp_size);
    printf("%lu-bit integer\n\n", sizeof(isvd_int_t) * 8);
  }
}
