#define isvd_@x@PostprocessTallSkinnyQr   isvd_@x@PostprocessTallSkinnyQr_gpu

#include <gtest/gtest.h>
#include "../../core/stage/@x@_postprocess_tall_skinny_qr.hxx"

TEST(@XStr@_TallSkinnyQrPostprocessing_Gpu, BlockCol_ColMajor_GatherUV) {
  test('C', 'C', GatherUV);
}

TEST(@XStr@_TallSkinnyQrPostprocessing_Gpu, BlockCol_RowMajor_GatherUV) {
  test('C', 'R', GatherUV);
}

TEST(@XStr@_TallSkinnyQrPostprocessing_Gpu, BlockRow_ColMajor_GatherUV) {
  test('R', 'C', GatherUV);
}

TEST(@XStr@_TallSkinnyQrPostprocessing_Gpu, BlockRow_RowMajor_GatherUV) {
  test('R', 'R', GatherUV);
}

TEST(@XStr@_TallSkinnyQrPostprocessing_Gpu, BlockCol_ColMajor_BlockUV) {
  test('C', 'C', BlockUV);
}

TEST(@XStr@_TallSkinnyQrPostprocessing_Gpu, BlockCol_RowMajor_BlockUV) {
  test('C', 'R', BlockUV);
}

TEST(@XStr@_TallSkinnyQrPostprocessing_Gpu, BlockRow_ColMajor_BlockUV) {
  test('R', 'C', BlockUV);
}

TEST(@XStr@_TallSkinnyQrPostprocessing_Gpu, BlockRow_RowMajor_BlockUV) {
  test('R', 'R', BlockUV);
}


TEST(@XStr@_TallSkinnyQrPostprocessing_Gpu, BlockCol_ColMajor_NoUV) {
  test('C', 'C', NoUV);
}

TEST(@XStr@_TallSkinnyQrPostprocessing_Gpu, BlockCol_RowMajor_NoUV) {
  test('C', 'R', NoUV);
}

TEST(@XStr@_TallSkinnyQrPostprocessing_Gpu, BlockRow_ColMajor_NoUV) {
  test('R', 'C', NoUV);
}

TEST(@XStr@_TallSkinnyQrPostprocessing_Gpu, BlockRow_RowMajor_NoUV) {
  test('R', 'R', NoUV);
}
