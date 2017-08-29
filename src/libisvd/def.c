////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/def.c
/// \brief      The information of iSVD.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/def.h>
#include <libisvd/def.h>
#include <libisvd/util/mpi.h>
#include <libisvd/util/omp.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  core_module
/// Display the information.
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
