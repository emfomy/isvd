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
    const char dista, const char ordera, const isvd_Param param,
    const double *a, const isvd_int_t lda, double *yst, const isvd_int_t ldyst, const isvd_int_t seed,
    const mpi_int_t mpi_root
);

// Orthogonalization
void isvd_dOrthogonalizeTallSkinnyQr(
    const isvd_Param param, double *yst, const isvd_int_t ldyst
);

void isvd_dOrthogonalizeGramian(
    const isvd_Param param, double *yst, const isvd_int_t ldyst
);

// Integration
isvd_int_t isvd_dIntegrateKolmogorovNagumo(
    const isvd_Param param, double *qst, const isvd_int_t ldqst, double *qt, const isvd_int_t ldqt,
    const isvd_int_t maxiter, const double tol
);

isvd_int_t isvd_dIntegrateWenYin(
    const isvd_Param param, double *qst, const isvd_int_t ldqst, double *qt, const isvd_int_t ldqt,
    const isvd_int_t maxiter, const double tol
);

// Postprocessing
void isvd_dPostprocessTallSkinnyQr(
    const isvd_int_t jobut, const isvd_int_t jobvt, const char dista, const char ordera, const isvd_Param param,
    const double *a, const isvd_int_t lda, const double *qt, const isvd_int_t ldqt,
    double *s, double *ut, const isvd_int_t ldut, double *vt, const isvd_int_t ldvt,
    const mpi_int_t mpi_root
);

void isvd_dPostprocessGramian(
    const isvd_int_t jobut, const isvd_int_t jobvt, const char dista, const char ordera, const isvd_Param param,
    const double *a, const isvd_int_t lda, const double *qt, const isvd_int_t ldqt,
    double *s, double *ut, const isvd_int_t ldut, double *vt, const isvd_int_t ldvt,
    const mpi_int_t mpi_root
);

void isvd_dPostprocessSymmetric(
    const isvd_int_t jobut, const char dista, const char ordera, const isvd_Param param,
    const double *a, const isvd_int_t lda, const double *qt, const isvd_int_t ldqt,
    double *s, double *ut, const isvd_int_t ldut,
    const mpi_int_t mpi_root
);

#endif  // _ISVD_CORE_DTYPE_H_
