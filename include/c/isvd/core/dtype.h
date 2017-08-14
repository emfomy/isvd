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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  core_dtype_s_module  Sketching Module (Double Precision)
/// @ingroup   core_dtype_module
/// @brief     The Sketching Module (Double Precision)
///
void isvd_dSketchGaussianProjection(
    const char dista, const char ordera, const isvd_Param param,
    const double *a, const isvd_int_t lda, double *yt, const isvd_int_t ldyt, const isvd_int_t seed,
    const mpi_int_t mpi_root
);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  core_dtype_o_module  Orthogonalization Module (Double Precision)
/// @ingroup   core_dtype_module
/// @brief     The Orthogonalization Module (Double Precision)
///
void isvd_dOrthogonalizeTallSkinnyQr(
    const isvd_Param param, double *yt, const isvd_int_t ldyt
);

void isvd_dOrthogonalizeGramian(
    const isvd_Param param, double *yt, const isvd_int_t ldyt
);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  core_dtype_i_module  Integration Module (Double Precision)
/// @ingroup   core_dtype_module
/// @brief     The Integration Module (Double Precision)
///
void isvd_dIntegrateKolmogorovNagumo(
    const isvd_Param param, double *yt, const isvd_int_t ldyt, double *qt, const isvd_int_t ldqt
);

void isvd_dIntegrateWenYin(
    const isvd_Param param, double *yt, const isvd_int_t ldyt, double *qt, const isvd_int_t ldqt
);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  core_dtype_p_module  Postprocessing Module (Double Precision)
/// @ingroup   core_dtype_module
/// @brief     The Postprocessing Module (Double Precision)
///
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
