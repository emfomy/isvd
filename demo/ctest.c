////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       demo/ctest.c
/// \brief      The C test code
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <stdio.h>
#include <stdlib.h>
#include <isvd.h>
#include <mpi.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  isvd_init(&argc, &argv, MPI_COMM_WORLD);

  const mpi_int_t mpi_size = isvd_getMpiSize(MPI_COMM_WORLD);
  const mpi_int_t mpi_rank = isvd_getMpiRank(MPI_COMM_WORLD);
  const mpi_int_t mpi_root = 0;

  if ( mpi_rank == mpi_root ) {
    printf("iSVD C demo\n");
    isvd_printEnvironment(MPI_COMM_WORLD);
  }

  const isvd_int_t m = 100;
  const isvd_int_t n = 1000;

  double *a = isvd_dmalloc(m * n);

  isvd_vdRngGaussianDriver(0, 0, m*n, a, 0.0, 1.0);

  isvd_finalize();

  return 0;
}
