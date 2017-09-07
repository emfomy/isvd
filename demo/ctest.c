////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       demo/ctest.c
/// \brief      The C test code
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <stdio.h>
#include <isvd.h>
#include <mpi.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  isvd_init(&argc, &argv, MPI_COMM_WORLD);

  mpi_int_t mpi_size = isvd_getMpiSize(MPI_COMM_WORLD);
  mpi_int_t mpi_rank = isvd_getMpiRank(MPI_COMM_WORLD);
  mpi_int_t mpi_root = 0;

  if ( mpi_rank == mpi_root ) {
    printf("iSVD C test\n");
    isvd_printEnvironment(MPI_COMM_WORLD);
  }

  isvd_finalize();

  return 0;
}
