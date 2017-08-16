////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/ctest.c
/// @brief   The C test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <stdio.h>
#include <stdlib.h>
#include <isvd.h>

typedef double isvd_val_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  MPI_Init(&argc, &argv);

  const mpi_int_t mpi_size = isvd_getMpiSize(MPI_COMM_WORLD);
  const mpi_int_t mpi_rank = isvd_getMpiRank(MPI_COMM_WORLD);
  const mpi_int_t mpi_root = 0;

  isvd_int_t omp_size = isvd_getOmpSize();

  if ( mpi_rank == mpi_root ) {
    printf("iSVD " ISVD_VERSION " C test\n");
    printf("%d nodes, %d threads per node\n\n", mpi_size, omp_size);
  }

  isvd_int_t seed = 0;

  isvd_dIsvd(
    "GP", "GR", "KN", "GR", 100, 1000, 20, 12, 4, 'C', 'C',
    NULL, 0, NULL, NULL, 0, NULL, 0, seed, mpi_root, -1, -1, MPI_COMM_WORLD);

  MPI_Finalize();

  return 0;
}
