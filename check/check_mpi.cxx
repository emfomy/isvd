#include <cstdio>
#include <iostream>
#include <gtest/gtest.h>
#include <mpi.h>
#include <isvd.h>

int main( int argc, char **argv ) {

  MPI_Init(&argc, &argv);

  if ( isvd_getMpiRank(MPI_COMM_WORLD) != 0 ) {
    std::fclose(stdout);
  }

  std::cout << "iSVD "
            << ISVD_MAJOR_VERSION << "."
            << ISVD_MINOR_VERSION << "."
            << ISVD_PATCH_VERSION << " "
            << ISVD_CHECK_NAME << std::endl << std::endl;

  std::cout << "Using " << isvd_getMpiSize(MPI_COMM_WORLD) << " MPI nodes." << std::endl << std::endl;

  testing::InitGoogleTest(&argc, argv);
  int retval = RUN_ALL_TESTS();
  assert(testing::UnitTest::GetInstance()->test_to_run_count() > 0);

  MPI_Finalize();

  return retval;
}
