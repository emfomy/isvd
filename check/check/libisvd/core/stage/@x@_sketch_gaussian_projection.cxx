#include <gtest/gtest.h>
#include "@x@_sketch_gaussian_projection.hxx"

TEST(@XStr@_GaussianProjectionSketching, BlockCol_ColMajor) {
  test('C', 'C');
}

TEST(@XStr@_GaussianProjectionSketching, BlockCol_RowMajor) {
  test('C', 'R');
}

TEST(@XStr@_GaussianProjectionSketching, BlockRow_ColMajor) {
  test('R', 'C');
}

TEST(@XStr@_GaussianProjectionSketching, BlockRow_RowMajor) {
  test('R', 'R');
}
