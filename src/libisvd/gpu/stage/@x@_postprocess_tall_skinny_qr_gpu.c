////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/gpu/stage/@x@_postprocess_tall_skinny_qr_gpu.c
/// \brief      The GPU Tall-Skinny QR Postprocessing (@xname@ precision)
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/gpu/@x@_stage.h>
#include <libisvd/gpu/def.h>
#include <libisvd/gpu/stage/@x@_postprocess_gpu.h>

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
#define isvd_@x@PostprocessTallSkinnyQr isvd_@x@PostprocessTallSkinnyQr_gpu
#endif  // DOXYGEN_SHOULD_SKIP_THIS

#include <libisvd/core/stage/@x@_postprocess_tall_skinny_qr.c>
