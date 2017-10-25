////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       demo/ctest.c
/// \brief      The C test code
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017 Mu Yang. All rights reserved.
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

  const isvd_int_t m = 100;
  const isvd_int_t k = 10;

  isvd_d_val_t *q = isvd_dMalloc(k * m);
  const isvd_int_t ldq = k;

  isvd_d_val_t *tau = isvd_dMalloc(k);

  isvd_dGelqf(k, m, q, ldq, tau);
  isvd_dOrglq(k, m, k, q, ldq, tau);

  isvd_Finalize();

  return 0;
}
