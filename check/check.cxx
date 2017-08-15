#include <iostream>
#include <gtest/gtest.h>
#include <isvd.h>

int main( int argc, char **argv ) {

  std::cout << "iSVD "
            << ISVD_MAJOR_VERSION << "."
            << ISVD_MINOR_VERSION << "."
            << ISVD_PATCH_VERSION << " "
            << ISVD_CHECK_NAME << std::endl << std::endl;

  testing::InitGoogleTest(&argc, argv);
  int retval = RUN_ALL_TESTS();
  assert(testing::UnitTest::GetInstance()->test_to_run_count() > 0);

  return retval;
}
