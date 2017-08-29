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

typedef double isvd_val_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  MPI_Init(&argc, &argv);

  const mpi_int_t mpi_size = isvd_getMpiSize(MPI_COMM_WORLD);
  const mpi_int_t mpi_rank = isvd_getMpiRank(MPI_COMM_WORLD);
  const mpi_int_t mpi_root = 0;

  omp_int_t omp_size = isvd_getOmpSize();

  if ( mpi_rank == mpi_root ) {
    printf("iSVD " ISVD_VERSION " C test\n");
    printf("%d nodes, %d threads per node\n", mpi_size, omp_size);
    printf("%lu-bit integer\n\n", sizeof(isvd_int_t) * 8);
  }

  const isvd_int_t mb = 100;
  const isvd_int_t nb = 1000;
  const isvd_int_t k  = 20;
  const isvd_int_t p  = 12;
  const isvd_int_t N  = 4;
  const isvd_int_t P  = mpi_size;

  const isvd_int_t m  = mb * P;
  const isvd_int_t n  = nb * P;
  const isvd_int_t l  = k+p;

  isvd_val_t *a = isvd_dmalloc(m * n);
  isvd_int_t lda = m;

  isvd_val_t *s = isvd_dmalloc(l);

  isvd_int_t seed = 0;

  isvd_VSLStreamStatePtr stream;
  isvd_vslNewStream(&stream, seed);
  isvd_vdRngGaussian(stream, m * n, a, 0.0, 1.0);
  isvd_vslDeleteStream(&stream);

  isvd_dIsvd(
    "GP", "GR", "KN", "GR", m, n, k, p, N, 'R', 'C',
    a + mb * mpi_rank, lda, s, nullptr, 0, nullptr, 0, seed, -2, -2, mpi_root, MPI_COMM_WORLD
  );

  isvd_dIeig(
    "GP", "GR", "KN", "SY", m, k, p, N, 'R', 'C',
    a + mb * mpi_rank, lda, s, nullptr, 0, seed, -2, mpi_root, MPI_COMM_WORLD
  );

  isvd_free(a);
  isvd_free(s);

  MPI_Finalize();

  return 0;
}
