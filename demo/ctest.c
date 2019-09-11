////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       demo/ctest.c
/// \brief      The C test code
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <stdio.h>
#include <stdlib.h>
#include <isvd.h>
#include <mpi.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  isvd_Init(&argc, &argv, MPI_COMM_WORLD);

  const mpi_int_t mpi_size = isvd_getMpiSize(MPI_COMM_WORLD);
  const mpi_int_t mpi_rank = isvd_getMpiRank(MPI_COMM_WORLD);
  const mpi_int_t mpi_root = 0;

  if ( mpi_rank == mpi_root ) {
    printf("iSVD C demo\n");
    isvd_PrintEnvironment(MPI_COMM_WORLD);
  }

  const isvd_int_t m = 100, n = 1000, k = 20, p = 12, N = 16;
  const isvd_Param param = isvd_createParam(m, n, k, p, N, mpi_root, MPI_COMM_WORLD);

  isvd_Finalize();

  return 0;
}
