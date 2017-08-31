////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       demo/ctest.c
/// \brief      The C test code
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <isvd.h>

typedef double isvd_val_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  MPI_Init(&argc, &argv);

  mpi_int_t mpi_root = 0;
  mpi_int_t mpi_rank;
  mpi_int_t mpi_size;
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

  isvd_printEnvironment(MPI_COMM_WORLD, mpi_root);

  const isvd_int_t mb = 100;
  const isvd_int_t nb = 1000;
  const isvd_int_t k  = 20;
  const isvd_int_t p  = 12;
  const isvd_int_t N  = 4;
  const isvd_int_t P  = mpi_size;

  const isvd_int_t m  = mb * P;
  const isvd_int_t n  = nb * P;
  const isvd_int_t l  = k+p;

  isvd_val_t *a = malloc(m * n * sizeof(isvd_val_t));
  isvd_int_t lda = m;

  isvd_val_t *s = malloc(l * sizeof(isvd_val_t));

  isvd_int_t seed = 0;

  srand(0);
  for ( isvd_int_t i = 0; i < m * n; ++i ) {
    isvd_val_t v = (isvd_val_t) rand() / RAND_MAX;
    a[i] = exp(-v * v) / 2.50662827463;
  }

  isvd_dIsvd(
    "GP", "GR", "KN", "GR", m, n, k, p, N, 'R', 'C',
    a + mb * mpi_rank, lda, s, NULL, 0, NULL, 0, seed, -2, -2, mpi_root, MPI_COMM_WORLD
  );

  isvd_dIeig(
    "GP", "GR", "KN", "SY", m, k, p, N, 'R', 'C',
    a + mb * mpi_rank, lda, s, NULL, 0, seed, -2, mpi_root, MPI_COMM_WORLD
  );

  free(a);
  free(s);

  MPI_Finalize();

  return 0;
}
