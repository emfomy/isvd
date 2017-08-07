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

  printf("iSVD " ISVD_VERSION " C test\n");

  isvd_dsgp('?', 'R', 0, 0, 0, 0, NULL, 0, NULL, 0, rand(), MPI_COMM_WORLD);

  return 0;
}
