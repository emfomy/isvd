#include <cstdio>
#include <iostream>
#include <gtest/gtest.h>
#include <mpi.h>
#include <isvd.h>
#include <libisvd.h>

int main( int argc, char **argv ) {

#if defined(ISVD_USE_GPU)
  isvd_init(&argc, &argv, MPI_COMM_WORLD);
#else  // ISVD_USE_GPU
  isvd_init_cpu(&argc, &argv, MPI_COMM_WORLD);
#endif  // ISVD_USE_GPU

  if ( isvd_getMpiRank(MPI_COMM_WORLD) != 0 ) {
    std::fclose(stdout);
  }

  printf("iSVD " ISVD_VERSION " " ISVD_CHECK_NAME " test\n\n");

#if defined(ISVD_USE_GPU)
  isvd_printEnvironment(MPI_COMM_WORLD);
#else  // ISVD_USE_GPU
  isvd_printEnvironment_cpu(MPI_COMM_WORLD);
#endif  // ISVD_USE_GPU

  testing::InitGoogleTest(&argc, argv);
  int retval = RUN_ALL_TESTS();
  assert(testing::UnitTest::GetInstance()->test_to_run_count() > 0);

#if defined(ISVD_USE_GPU)
  isvd_finalize();
#else  // ISVD_USE_GPU
  isvd_finalize_cpu();
#endif  // ISVD_USE_GPU

  return retval;
}
