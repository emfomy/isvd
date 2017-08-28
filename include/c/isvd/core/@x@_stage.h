////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/core/@x@_stage.h
/// \brief      The iSVD stages.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _ISVD_CORE_@X@_STAGE_H_
#define _ISVD_CORE_@X@_STAGE_H_

#include <isvd/core/def.h>
#include <isvd/core/param.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

// Sketching
void isvd_@x@SketchGaussianProjection(
    const isvd_Param param, const @xtype@ *argv, const isvd_int_t argc, @xtype@ *retv, const isvd_int_t retc,
    const char dista, const char ordera, const @xtype@ *a, const isvd_int_t lda,
    @xtype@ *yst, const isvd_int_t ldyst, const isvd_int_t seed, const mpi_int_t mpi_root
);

// Orthogonalization
void isvd_@x@OrthogonalizeTallSkinnyQr(
    const isvd_Param param, const @xtype@ *argv, const isvd_int_t argc, @xtype@ *retv, const isvd_int_t retc,
    @xtype@ *yst, const isvd_int_t ldyst
);

void isvd_@x@OrthogonalizeGramian(
    const isvd_Param param, const @xtype@ *argv, const isvd_int_t argc, @xtype@ *retv, const isvd_int_t retc,
    @xtype@ *yst, const isvd_int_t ldyst
);

// Integration
void isvd_@x@IntegrateKolmogorovNagumo(
    const isvd_Param param, const @xtype@ *argv, const isvd_int_t argc, @xtype@ *retv, const isvd_int_t retc,
    const @xtype@ *yst, const isvd_int_t ldyst, @xtype@ *qt, const isvd_int_t ldqt
);

void isvd_@x@IntegrateWenYin(
    const isvd_Param param, const @xtype@ *argv, const isvd_int_t argc, @xtype@ *retv, const isvd_int_t retc,
    const @xtype@ *yst, const isvd_int_t ldyst, @xtype@ *qt, const isvd_int_t ldqt
);

void isvd_@x@IntegrateHierarchicalReduction(
    const isvd_Param param, const @xtype@ *argv, const isvd_int_t argc, @xtype@ *retv, const isvd_int_t retc,
          @xtype@ *yst, const isvd_int_t ldyst, @xtype@ *qt, const isvd_int_t ldqt
);

// Postprocessing
void isvd_@x@PostprocessTallSkinnyQr(
    const isvd_Param param, const @xtype@ *argv, const isvd_int_t argc, @xtype@ *retv, const isvd_int_t retc,
    const char dista, const char ordera, const @xtype@ *a, const isvd_int_t lda, const @xtype@ *qt, const isvd_int_t ldqt,
    @xtype@ *s, @xtype@ *ut, const isvd_int_t ldut, @xtype@ *vt, const isvd_int_t ldvt,
    const mpi_int_t ut_root, const mpi_int_t vt_root
);

void isvd_@x@PostprocessGramian(
    const isvd_Param param, const @xtype@ *argv, const isvd_int_t argc, @xtype@ *retv, const isvd_int_t retc,
    const char dista, const char ordera, const @xtype@ *a, const isvd_int_t lda, const @xtype@ *qt, const isvd_int_t ldqt,
    @xtype@ *s, @xtype@ *ut, const isvd_int_t ldut, @xtype@ *vt, const isvd_int_t ldvt,
    const mpi_int_t ut_root, const mpi_int_t vt_root
);

void isvd_@x@PostprocessSymmetric(
    const isvd_Param param, const @xtype@ *argv, const isvd_int_t argc, @xtype@ *retv, const isvd_int_t retc,
    const char dista, const char ordera, const @xtype@ *a, const isvd_int_t lda, const @xtype@ *qt, const isvd_int_t ldqt,
    @xtype@ *s, @xtype@ *ut, const isvd_int_t ldut,
    const mpi_int_t ut_root
);

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_CORE_@X@_STAGE_H_
