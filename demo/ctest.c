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
    printf("%d nodes, %d threads per node\n", mpi_size, omp_size);
  }

  isvd_int_t n  = 1001;
  isvd_int_t Nl = 132;
  isvd_val_t *omegat = isvd_dmalloc(n * Nl);

  VSLStreamStatePtr stream;
  vslNewStream(&stream, VSL_BRNG_SFMT19937, 0);
  vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER, stream, n * Nl, omegat, 0.0, 1.0);

  FILE *file = fopen("omega.mtx", "w");
  for ( isvd_int_t j = 0; j < Nl; ++j ) {
    for ( isvd_int_t i = 0; i < n; ++i ) {
      fprintf(file, "%20.16g\n", omegat[i*Nl+j]);
    }
  }

  isvd_free(omegat);

  // const isvd_Param param = isvd_createParam(11, 13, 2, 1, 1, 0, MPI_COMM_WORLD);
  // const isvd_int_t seed = 0;

  // isvd_int_t m   = param.nrow;
  // isvd_int_t mb  = param.nrow_each;
  // isvd_int_t n   = param.ncol;
  // isvd_int_t nb  = param.ncol_each;
  // isvd_int_t l   = param.dim_sketch;
  // isvd_int_t Nl  = param.dim_sketch_total;

  // isvd_val_t *a = isvd_dmalloc(m * n);
  // isvd_int_t lda = m;
  // for ( isvd_int_t i = 0; i < m * n; ++i ) {
  //   a[i] = i*i;
  // }

  // isvd_val_t *yst = isvd_dmalloc(mb * Nl);
  // isvd_int_t ldyst = Nl;

  // isvd_val_t *qt = isvd_dmalloc(mb * l);
  // isvd_int_t ldqt = l;

  // isvd_dSketchGaussianProjection('C', 'C', param, a + m * nb * param.mpi_rank, lda, yst, ldyst, seed, mpi_root);
  // // isvd_dSketchGaussianProjection('R', 'C', param, a + mb * param.mpi_rank, lda, yst, ldyst, seed, mpi_root);

  // isvd_dOrthogonalizeGramian(param, yst, ldyst);

  // isvd_dIntegrateKolmogorovNagumo(param, yst, ldyst, qt, ldqt, 256, 1e-4);

  // isvd_mrdisp("%lf", mb, l, ldqt, qt);

  MPI_Finalize();

  return 0;
}
