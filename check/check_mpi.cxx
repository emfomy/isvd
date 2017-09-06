#include <cstdio>
#include <iostream>
#include <gtest/gtest.h>
#include <mpi.h>
#include <isvd.h>
#include <libisvd.h>

int main( int argc, char **argv ) {

  isvd_init(&argc, &argv, MPI_COMM_WORLD);

  if ( isvd_getMpiRank(MPI_COMM_WORLD) != 0 ) {
    std::fclose(stdout);
  }

  printf("iSVD " ISVD_CHECK_NAME " unit test\n");
  isvd_printEnvironment(MPI_COMM_WORLD);

  testing::InitGoogleTest(&argc, argv);
  int retval = RUN_ALL_TESTS();
  assert(testing::UnitTest::GetInstance()->test_to_run_count() > 0);

  isvd_finalize();

  return retval;
}
