#include <gtest/gtest.h>
#include "@x@_postprocess_symmetric.hxx"

TEST(@XStr@_SymmetricPostprocessing, BlockCol_ColMajor_GatherUV) {
  test('C', 'C', GatherUV);
}

TEST(@XStr@_SymmetricPostprocessing, BlockCol_RowMajor_GatherUV) {
  test('C', 'R', GatherUV);
}

TEST(@XStr@_SymmetricPostprocessing, BlockRow_ColMajor_GatherUV) {
  test('R', 'C', GatherUV);
}

TEST(@XStr@_SymmetricPostprocessing, BlockRow_RowMajor_GatherUV) {
  test('R', 'R', GatherUV);
}

TEST(@XStr@_SymmetricPostprocessing, BlockCol_ColMajor_BlockUV) {
  test('C', 'C', BlockUV);
}

TEST(@XStr@_SymmetricPostprocessing, BlockCol_RowMajor_BlockUV) {
  test('C', 'R', BlockUV);
}

TEST(@XStr@_SymmetricPostprocessing, BlockRow_ColMajor_BlockUV) {
  test('R', 'C', BlockUV);
}

TEST(@XStr@_SymmetricPostprocessing, BlockRow_RowMajor_BlockUV) {
  test('R', 'R', BlockUV);
}


TEST(@XStr@_SymmetricPostprocessing, BlockCol_ColMajor_NoUV) {
  test('C', 'C', NoUV);
}

TEST(@XStr@_SymmetricPostprocessing, BlockCol_RowMajor_NoUV) {
  test('C', 'R', NoUV);
}

TEST(@XStr@_SymmetricPostprocessing, BlockRow_ColMajor_NoUV) {
  test('R', 'C', NoUV);
}

TEST(@XStr@_SymmetricPostprocessing, BlockRow_RowMajor_NoUV) {
  test('R', 'R', NoUV);
}
