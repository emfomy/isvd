////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/core/@x@_stage.h
/// \brief      The iSVD stages.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef ISVD_CORE_@X@_STAGE_H_
#define ISVD_CORE_@X@_STAGE_H_

#include <isvd/def.h>
#include <isvd/core/param.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

// Sketching
void isvd_@x@SketchGaussianProjection(
    const isvd_Param param, const @xtype_____@ *argv, const isvd_int_t argc, @xtype_____@ *retv, const isvd_int_t retc,
    const char dista, const char ordera, const @xtype_____@ *a, const isvd_int_t lda,
    @xtype_____@ *yst, const isvd_int_t ldyst, const isvd_int_t seed, const mpi_int_t mpi_root
);

// Orthogonalization
void isvd_@x@OrthogonalizeTallSkinnyQr(
    const isvd_Param param, const @xtype_____@ *argv, const isvd_int_t argc, @xtype_____@ *retv, const isvd_int_t retc,
    @xtype_____@ *yst, const isvd_int_t ldyst
);

void isvd_@x@OrthogonalizeGramian(
    const isvd_Param param, const @xtype_____@ *argv, const isvd_int_t argc, @xtype_____@ *retv, const isvd_int_t retc,
    @xtype_____@ *yst, const isvd_int_t ldyst
);

// Integration
void isvd_@x@IntegrateKolmogorovNagumo(
    const isvd_Param param, const @xtype_____@ *argv, const isvd_int_t argc, @xtype_____@ *retv, const isvd_int_t retc,
    const @xtype_____@ *yst, const isvd_int_t ldyst, @xtype_____@ *qt, const isvd_int_t ldqt
);

void isvd_@x@IntegrateWenYin(
    const isvd_Param param, const @xtype_____@ *argv, const isvd_int_t argc, @xtype_____@ *retv, const isvd_int_t retc,
    const @xtype_____@ *yst, const isvd_int_t ldyst, @xtype_____@ *qt, const isvd_int_t ldqt
);

void isvd_@x@IntegrateHierarchicalReduction(
    const isvd_Param param, const @xtype_____@ *argv, const isvd_int_t argc, @xtype_____@ *retv, const isvd_int_t retc,
          @xtype_____@ *yst, const isvd_int_t ldyst, @xtype_____@ *qt, const isvd_int_t ldqt
);

// Postprocessing
void isvd_@x@PostprocessTallSkinnyQr(
    const isvd_Param param, const @xtype_____@ *argv, const isvd_int_t argc, @xtype_____@ *retv, const isvd_int_t retc,
    const char dista, const char ordera,
    const @xtype_____@ *a, const isvd_int_t lda, const @xtype_____@ *qt, const isvd_int_t ldqt,
    @xtype_____@ *s, @xtype_____@ *ut, const isvd_int_t ldut, @xtype_____@ *vt, const isvd_int_t ldvt,
    const mpi_int_t ut_root, const mpi_int_t vt_root
);

void isvd_@x@PostprocessGramian(
    const isvd_Param param, const @xtype_____@ *argv, const isvd_int_t argc, @xtype_____@ *retv, const isvd_int_t retc,
    const char dista, const char ordera,
    const @xtype_____@ *a, const isvd_int_t lda, const @xtype_____@ *qt, const isvd_int_t ldqt,
          @xtype_____@ *s, @xtype_____@ *ut, const isvd_int_t ldut, @xtype_____@ *vt, const isvd_int_t ldvt,
    const mpi_int_t ut_root, const mpi_int_t vt_root
);

void isvd_@x@PostprocessSymmetric(
    const isvd_Param param, const @xtype_____@ *argv, const isvd_int_t argc, @xtype_____@ *retv, const isvd_int_t retc,
    const char dista, const char ordera,
    const @xtype_____@ *a, const isvd_int_t lda, const @xtype_____@ *qt, const isvd_int_t ldqt,
          @xtype_____@ *s, @xtype_____@ *ut, const isvd_int_t ldut, @xtype_____@ *vt, const isvd_int_t ldvt,
    const mpi_int_t ut_root, const mpi_int_t vt_root
);

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_CORE_@X@_STAGE_H_
