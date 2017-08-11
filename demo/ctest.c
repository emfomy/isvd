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

  const struct isvd_Param param = isvd_createParam(100, 1000, 20, 12, 16, 0, MPI_COMM_WORLD);
  // isvd_disp("%d", param.nrow);
  // isvd_disp("%d", param.ncol);
  // isvd_disp("%d", param.nrow_proc);
  // isvd_disp("%d", param.ncol_proc);
  // isvd_disp("%d", param.nrow_per);
  // isvd_disp("%d", param.ncol_per);
  // isvd_disp("%d", param.nrow_total);
  // isvd_disp("%d", param.ncol_total);
  isvd_disp("%d", param.rowrange.begin);
  isvd_disp("%d", param.rowrange.end);
  isvd_disp("%d", param.colrange.begin);
  isvd_disp("%d", param.colrange.end);
  // isvd_disp("%d", param.rank);
  // isvd_disp("%d", param.over_rank);
  // isvd_disp("%d", param.dim_sketch);
  // isvd_disp("%d", param.dim_sketch_total);
  // isvd_disp("%d", param.num_sketch);

  // isvd_dSketchGaussianProjection('?', 'R', 0, 0, 0, 0, NULL, 0, NULL, 0, rand(), MPI_COMM_WORLD);

  MPI_Finalize();

  return 0;
}
