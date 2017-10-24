////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/gpu/stage/@x@_postprocess_gramian_gpu.c
/// \brief      The GPU Gramian Postprocessing (@xname@ precision).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/gpu/@x@_stage.h>
#include <libisvd/gpu/def.h>
#include <libisvd/gpu/stage/@x@_postprocess_gpu.h>

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
#define isvd_@x@PostprocessGramian isvd_@x@PostprocessGramian_gpu
#endif  // DOXYGEN_SHOULD_SKIP_THIS

#include <libisvd/core/stage/@x@_postprocess_gramian.c>
