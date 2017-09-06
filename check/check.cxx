#include <iostream>
#include <gtest/gtest.h>
#include <isvd.h>

int main( int argc, char **argv ) {

  printf("iSVD " ISVD_CHECK_NAME " unit test\n");
  isvd_printEnvironment(MPI_COMM_WORLD);

  testing::InitGoogleTest(&argc, argv);
  int retval = RUN_ALL_TESTS();
  assert(testing::UnitTest::GetInstance()->test_to_run_count() > 0);

  return retval;
}
