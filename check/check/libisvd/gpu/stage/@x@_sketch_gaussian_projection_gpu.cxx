#define isvd_@x@SketchGaussianProjection   isvd_@x@SketchGaussianProjection_gpu

#include <gtest/gtest.h>
#include "../../core/stage/@x@_sketch_gaussian_projection.hxx"

TEST(@XStr@_GaussianProjectionSketching_Gpu, BlockCol_ColMajor) {
  test('C', 'C');
}

TEST(@XStr@_GaussianProjectionSketching_Gpu, BlockCol_RowMajor) {
  test('C', 'R');
}

TEST(@XStr@_GaussianProjectionSketching_Gpu, BlockRow_ColMajor) {
  test('R', 'C');
}

TEST(@XStr@_GaussianProjectionSketching_Gpu, BlockRow_RowMajor) {
  test('R', 'R');
}
