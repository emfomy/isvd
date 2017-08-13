////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/ctest.c
/// @brief   The C test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <stdio.h>
#include <stdlib.h>
#include <isvd.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  MPI_Init(&argc, &argv);

  printf("iSVD " ISVD_VERSION " C test\n");

  const isvd_Param param = isvd_createParam(11, 13, 2, 1, 1, 0, MPI_COMM_WORLD);

  isvd_int_t m   = param.nrow;
  isvd_int_t mj  = param.nrow_proc;
  isvd_int_t mb  = param.nrow_each;
  isvd_int_t n   = param.ncol;
  isvd_int_t nj  = param.ncol_proc;
  isvd_int_t Nl  = param.dim_sketch_total;

  // double *a = isvd_dmalloc(m * nj);
  // isvd_int_t lda = m;
  // #pragma warning
  // isvd_int_t iseed[] = {0, 0, 0, 1};
  // LAPACKE_dlarnv(3, iseed, m * nj, a);

  double *a = isvd_dmalloc(mj * n);
  isvd_int_t lda = mj;
  #pragma warning
  isvd_int_t iseed[] = {0, 0, 0, 1};
  LAPACKE_dlarnv(3, iseed, mj * n, a);

  double *yt = isvd_dmalloc(mb * Nl);
  isvd_int_t ldyt = Nl;

  isvd_dSketchGaussianProjection('R', 'C', param, a, lda, yt, ldyt, rand());

  isvd_mrdisp("%lf", mb, Nl, Nl, yt);

  MPI_Finalize();

  return 0;
}
