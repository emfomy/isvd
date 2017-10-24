////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/gpu/stage/@x@_postprocess_tall_skinny_qr_gpu.c
/// \brief      The GPU Tall-Skinny QR Postprocessing (@xname@ precision).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/gpu/@x@_stage.h>
#include <libisvd/gpu/def.h>
#include <libisvd/gpu/stage/@x@_postprocess_gpu.h>

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
#define isvd_@x@PostprocessTallSkinnyQr isvd_@x@PostprocessTallSkinnyQr_gpu
#endif  // DOXYGEN_SHOULD_SKIP_THIS

#include <libisvd/core/stage/@x@_postprocess_tall_skinny_qr.c>
