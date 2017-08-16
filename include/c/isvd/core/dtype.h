////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/core/dtype.h
/// @brief   The core header for double precision.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_CORE_DTYPE_H_
#define _ISVD_CORE_DTYPE_H_

#include <isvd/core/def.h>
#include <isvd/core/param.h>

// Sketching
void isvd_dSketchGaussianProjection(
    const isvd_Param param, const double *args, const isvd_int_t largs, double *rets, const isvd_int_t lrets,
    const char dista, const char ordera, const double *a, const isvd_int_t lda,
    double *yst, const isvd_int_t ldyst, const isvd_int_t seed,
    const mpi_int_t mpi_root
);

// Orthogonalization
void isvd_dOrthogonalizeTallSkinnyQr(
    const isvd_Param param, const double *args, const isvd_int_t largs, double *rets, const isvd_int_t lrets,
    double *yst, const isvd_int_t ldyst
);

void isvd_dOrthogonalizeGramian(
    const isvd_Param param, const double *args, const isvd_int_t largs, double *rets, const isvd_int_t lrets,
    double *yst, const isvd_int_t ldyst
);

// Integration
void isvd_dIntegrateKolmogorovNagumo(
    const isvd_Param param, const double *args, const isvd_int_t largs, double *rets, const isvd_int_t lrets,
    const double *qst, const isvd_int_t ldqst, double *qt, const isvd_int_t ldqt
);

void isvd_dIntegrateWenYin(
    const isvd_Param param, const double *args, const isvd_int_t largs, double *rets, const isvd_int_t lrets,
    const double *qst, const isvd_int_t ldqst, double *qt, const isvd_int_t ldqt
);

// Postprocessing
void isvd_dPostprocessTallSkinnyQr(
    const isvd_Param param, const double *args, const isvd_int_t largs, double *rets, const isvd_int_t lrets,
    const char dista, const char ordera, const double *a, const isvd_int_t lda, const double *qt, const isvd_int_t ldqt,
    double *s, double *ut, const isvd_int_t ldut, double *vt, const isvd_int_t ldvt,
    const mpi_int_t ut_root, const mpi_int_t vt_root
);

void isvd_dPostprocessGramian(
    const isvd_Param param, const double *args, const isvd_int_t largs, double *rets, const isvd_int_t lrets,
    const char dista, const char ordera, const double *a, const isvd_int_t lda, const double *qt, const isvd_int_t ldqt,
    double *s, double *ut, const isvd_int_t ldut, double *vt, const isvd_int_t ldvt,
    const mpi_int_t ut_root, const mpi_int_t vt_root
);

void isvd_dPostprocessSymmetric(
    const isvd_Param param, const double *args, const isvd_int_t largs, double *rets, const isvd_int_t lrets,
    const char dista, const char ordera, const double *a, const isvd_int_t lda, const double *qt, const isvd_int_t ldqt,
    double *s, double *ut, const isvd_int_t ldut,
    const mpi_int_t ut_root
);

#endif  // _ISVD_CORE_DTYPE_H_
