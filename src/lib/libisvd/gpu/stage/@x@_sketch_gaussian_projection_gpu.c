////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/gpu/stage/@x@_sketch_gaussian_projection_gpu.c
/// \brief      The GPU Gaussian Projection Sketching (@xname@ precision).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/gpu/@x@_stage.h>
#include <libisvd/gpu/def.h>
#include <libisvd/gpu/stage/@x@_sketch_gpu.h>

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
#define isvd_@x@SketchGaussianProjection isvd_@x@SketchGaussianProjection_gpu
#endif  // DOXYGEN_SHOULD_SKIP_THIS

#include <libisvd/core/stage/@x@_sketch_gaussian_projection.c>
