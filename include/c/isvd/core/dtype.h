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
    const char storea, const char ordera, const isvd_Param param,
    const double *a, const isvd_int_t lda, double *y, const isvd_int_t ldy, const isvd_int_t seed
);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  core_dtype_o_module  Orthogonalization Module (Double Precision)
/// @ingroup   core_dtype_module
/// @brief     The Orthogonalization Module (Double Precision)
///
void isvd_dOrthogonalizeTsqr(
    const isvd_Param param, double *y, const isvd_int_t ldy
);

void isvd_dOrthogonalizeGramian(
    const isvd_Param param, double *y, const isvd_int_t ldy
);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  core_dtype_i_module  Integration Module (Double Precision)
/// @ingroup   core_dtype_module
/// @brief     The Integration Module (Double Precision)
///
void isvd_dIntegrateKolmogorovNagumo(
    const isvd_Param param, double *y, const isvd_int_t ldy, double *q, const isvd_int_t ldq
);

void isvd_dIntegrateWenYin(
    const isvd_Param param, double *y, const isvd_int_t ldy, double *q, const isvd_int_t ldq
);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  core_dtype_p_module  Postprocessing Module (Double Precision)
/// @ingroup   core_dtype_module
/// @brief     The Postprocessing Module (Double Precision)
///
void isvd_dPostprocessTsqr(
    const isvd_int_t jobu, const isvd_int_t jobv, const char storea,
    const char ordera, const char majoru, const char majorv, const isvd_Param param,
    const double *a, const isvd_int_t lda, const double *q, const isvd_int_t ldq,
    double *s, double *u, const isvd_int_t ldu, double *v, const isvd_int_t ldv,
    const mpi_int_t mpi_root
);

void isvd_dPostprocessGramian(
    const isvd_int_t jobu, const isvd_int_t jobv, const char storea,
    const char ordera, const char majoru, const char majorv, const isvd_Param param,
    const double *a, const isvd_int_t lda, const double *q, const isvd_int_t ldq,
    double *s, double *u, const isvd_int_t ldu, double *v, const isvd_int_t ldv,
    const mpi_int_t mpi_root
);

void isvd_dPostprocessSymmetric(
    const isvd_int_t jobu, const char storea, const char ordera, const char majoru, const isvd_Param param,
    const double *a, const isvd_int_t lda, const double *q, const isvd_int_t ldq,
    double *s, double *u, const isvd_int_t ldu,
    const mpi_int_t mpi_root
);

#endif  // _ISVD_CORE_DTYPE_H_
