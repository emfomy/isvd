////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/core/driver_d.h
/// @brief   The double precision drivers.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_CORE_DRIVER_D_H_
#define _ISVD_CORE_DRIVER_D_H_

#include <isvd/core/def.h>
#include <isvd/core/param.h>
#include <isvd/core/stage_d.h>
#include <isvd/util/arg.h>

// General iSVD driver
void isvd_dIsvd(
    const char *algs, const char *algo, const char *algi, const char *algp,
    const isvd_int_t m, const isvd_int_t n, const isvd_int_t k, const isvd_int_t p, const isvd_int_t N,
    const char dista, const char ordera, const double *a, const isvd_int_t lda,
    double *s, double *ut, const isvd_int_t ldut, double *vt, const isvd_int_t ldvt,
    const isvd_int_t seed, const mpi_int_t ut_root, const mpi_int_t vt_root,
    const mpi_int_t mpi_root, const MPI_Comm mpi_comm
);

// Symmetric iSVD driver
void isvd_dIeig(
    const char *algs, const char *algo, const char *algi, const char *algp,
    const isvd_int_t m, const isvd_int_t k, const isvd_int_t p, const isvd_int_t N,
    const char dista, const char ordera, const double *a, const isvd_int_t lda,
    double *s, double *ut, const isvd_int_t ldut,
    const isvd_int_t seed, const mpi_int_t ut_root,
    const mpi_int_t mpi_root, const MPI_Comm mpi_comm
);

typedef void (*isvd_fun_t)(isvd_Param, ...);

static inline isvd_fun_t isvd_arg2algs( const int16_t arg ) {
  switch ( arg ) {
    case isvd_char2('G', 'P'): return (isvd_fun_t) isvd_dSketchGaussianProjection;
    default: fprintf(stderr, "Unknown sketching abbreviation \"%c%c\"!\n", (arg & 0xff), ((arg >> 8) &0xff));
  }
  return NULL;
}

static inline isvd_fun_t isvd_arg2algo( const int16_t arg ) {
  switch ( arg ) {
    case isvd_char2('T', 'S'): return (isvd_fun_t) isvd_dOrthogonalizeTallSkinnyQr;
    case isvd_char2('G', 'R'): return (isvd_fun_t) isvd_dOrthogonalizeGramian;
    default: fprintf(stderr, "Unknown orthogonalization abbreviation \"%c%c\"!\n", (arg & 0xff), ((arg >> 8) &0xff));
  }
  return NULL;
}

static inline isvd_fun_t isvd_arg2algi( const int16_t arg ) {
  switch ( arg ) {
    case isvd_char2('K', 'N'): return (isvd_fun_t) isvd_dIntegrateKolmogorovNagumo;
    case isvd_char2('W', 'Y'): return (isvd_fun_t) isvd_dIntegrateWenYin;
    case isvd_char2('H', 'R'): return (isvd_fun_t) isvd_dIntegrateHierarchicalReduction;
    default: fprintf(stderr, "Unknown integration abbreviation \"%c%c\"!\n", (arg & 0xff), ((arg >> 8) &0xff));
  }
  return NULL;
}

static inline isvd_fun_t isvd_arg2algp( const int16_t arg ) {
  switch ( arg ) {
    case isvd_char2('T', 'S'): return (isvd_fun_t) isvd_dPostprocessTallSkinnyQr;
    case isvd_char2('G', 'R'): return (isvd_fun_t) isvd_dPostprocessGramian;
    case isvd_char2('S', 'Y'): return (isvd_fun_t) isvd_dPostprocessSymmetric;
    default: fprintf(stderr, "Unknown postprocess abbreviation \"%c%c\"!\n", (arg & 0xff), ((arg >> 8) &0xff));
  }
  return NULL;
}

#endif  // _ISVD_CORE_DRIVER_D_H_
