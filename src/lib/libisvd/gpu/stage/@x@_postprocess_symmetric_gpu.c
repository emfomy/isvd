////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/gpu/stage/@x@_postprocess_symmetric_gpu.c
/// \brief      The GPU Symmetric Postprocessing (@xname@ precision).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/gpu/@x@_stage.h>
#include <libisvd/gpu/def.h>
#include <libisvd/gpu/stage/@x@_postprocess_gpu.h>

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
#define isvd_@x@PostprocessSymmetric isvd_@x@PostprocessSymmetric_gpu
#endif  // DOXYGEN_SHOULD_SKIP_THIS

#include <libisvd/core/stage/@x@_postprocess_symmetric.c>
