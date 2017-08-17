#include <iostream>
#include <gtest/gtest.h>
#include <isvd.h>

int main( int argc, char **argv ) {

  isvd_int_t mpi_size = 1;
  isvd_int_t omp_size = isvd_getOmpSize();
  printf("iSVD " ISVD_VERSION " " ISVD_CHECK_NAME " test\n");
  printf("%d nodes, %d threads per node\n\n", mpi_size, omp_size);

  testing::InitGoogleTest(&argc, argv);
  int retval = RUN_ALL_TESTS();
  assert(testing::UnitTest::GetInstance()->test_to_run_count() > 0);

  return retval;
}
