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

  const isvd_Param param = isvd_createParam(100, 1000, 20, 12, 16, 0, MPI_COMM_WORLD);

  isvd_dSketchGaussianProjection('?', 'R', param, NULL, 0, NULL, 0, rand());

  MPI_Finalize();

  return 0;
}
