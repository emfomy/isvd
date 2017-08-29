#include <cstdio>
#include <iostream>
#include <gtest/gtest.h>
#include <mpi.h>
#include <isvd.h>
#include <libisvd.h>

int main( int argc, char **argv ) {

  MPI_Init(&argc, &argv);

  if ( isvd_getMpiRank(MPI_COMM_WORLD) != 0 ) {
    std::fclose(stdout);
  }

  mpi_int_t mpi_size = isvd_getMpiSize(MPI_COMM_WORLD);
  omp_int_t omp_size = isvd_getOmpSize();
  printf("iSVD " ISVD_VERSION " " ISVD_CHECK_NAME " test\n");
  printf("%d nodes, %d threads per node\n\n", mpi_size, omp_size);

  testing::InitGoogleTest(&argc, argv);
  int retval = RUN_ALL_TESTS();
  assert(testing::UnitTest::GetInstance()->test_to_run_count() > 0);

  MPI_Finalize();

  return retval;
}
