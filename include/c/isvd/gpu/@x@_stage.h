////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/gpu/@x@_stage.h
/// \brief      The iSVD stages with GPU support.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _ISVD_GPU_@X@_STAGE_H_
#define _ISVD_GPU_@X@_STAGE_H_

#include <isvd/def.h>
#include <isvd/core/param.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

// Sketching
void isvd_@x@SketchGaussianProjection_gpu(
    const isvd_Param param, const @xtype@ *argv, const isvd_int_t argc, @xtype@ *retv, const isvd_int_t retc,
    const char dista, const char ordera, const @xtype@ *a, const isvd_int_t lda,
    @xtype@ *yst, const isvd_int_t ldyst, const isvd_int_t seed, const mpi_int_t mpi_root
);

// Postprocessing
void isvd_@x@PostprocessTallSkinnyQr_gpu(
    const isvd_Param param, const @xtype@ *argv, const isvd_int_t argc, @xtype@ *retv, const isvd_int_t retc,
    const char dista, const char ordera, const @xtype@ *a, const isvd_int_t lda, const @xtype@ *qt, const isvd_int_t ldqt,
    @xtype@ *s, @xtype@ *ut, const isvd_int_t ldut, @xtype@ *vt, const isvd_int_t ldvt,
    const mpi_int_t ut_root, const mpi_int_t vt_root
);

void isvd_@x@PostprocessGramian_gpu(
    const isvd_Param param, const @xtype@ *argv, const isvd_int_t argc, @xtype@ *retv, const isvd_int_t retc,
    const char dista, const char ordera, const @xtype@ *a, const isvd_int_t lda, const @xtype@ *qt, const isvd_int_t ldqt,
    @xtype@ *s, @xtype@ *ut, const isvd_int_t ldut, @xtype@ *vt, const isvd_int_t ldvt,
    const mpi_int_t ut_root, const mpi_int_t vt_root
);

void isvd_@x@PostprocessSymmetric_gpu(
    const isvd_Param param, const @xtype@ *argv, const isvd_int_t argc, @xtype@ *retv, const isvd_int_t retc,
    const char dista, const char ordera, const @xtype@ *a, const isvd_int_t lda, const @xtype@ *qt, const isvd_int_t ldqt,
    @xtype@ *s, @xtype@ *ut, const isvd_int_t ldut,
    const mpi_int_t ut_root
);

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_GPU_@X@_STAGE_H_
