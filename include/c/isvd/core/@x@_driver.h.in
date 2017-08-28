////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file    include/c/isvd/core/@x@_driver.h
/// \brief   The @xtype@ precision drivers.
///
/// \author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_CORE_@X@_DRIVER_H_
#define _ISVD_CORE_@X@_DRIVER_H_

#include <isvd/core/def.h>
#include <isvd/core/param.h>
#include <isvd/core/@x@_stage.h>
#include <isvd/util/arg.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

// General iSVD driver
void isvd_@x@Isvd(
    const char *algs, const char *algo, const char *algi, const char *algp,
    const isvd_int_t m, const isvd_int_t n, const isvd_int_t k, const isvd_int_t p, const isvd_int_t N,
    const char dista, const char ordera, const @xtype@ *a, const isvd_int_t lda,
    @xtype@ *s, @xtype@ *ut, const isvd_int_t ldut, @xtype@ *vt, const isvd_int_t ldvt,
    const isvd_int_t seed, const mpi_int_t ut_root, const mpi_int_t vt_root,
    const mpi_int_t mpi_root, const MPI_Comm mpi_comm
);

// Symmetric iSVD driver
void isvd_@x@Ieig(
    const char *algs, const char *algo, const char *algi, const char *algp,
    const isvd_int_t m, const isvd_int_t k, const isvd_int_t p, const isvd_int_t N,
    const char dista, const char ordera, const @xtype@ *a, const isvd_int_t lda,
    @xtype@ *s, @xtype@ *ut, const isvd_int_t ldut,
    const isvd_int_t seed, const mpi_int_t ut_root,
    const mpi_int_t mpi_root, const MPI_Comm mpi_comm
);

static inline isvd_fun_t isvd_arg2@x@algs( const int16_t arg ) {
  switch ( arg ) {
    case isvd_char2('G', 'P'): return (isvd_fun_t) isvd_@x@SketchGaussianProjection;
    default: fprintf(stderr, "Unknown sketching abbreviation \"%c%c\"!\n", (arg & 0xff), ((arg >> 8) & 0xff));
  }
  return NULL;
}

static inline isvd_fun_t isvd_arg2@x@algo( const int16_t arg ) {
  switch ( arg ) {
    case isvd_char2('T', 'S'): return (isvd_fun_t) isvd_@x@OrthogonalizeTallSkinnyQr;
    case isvd_char2('G', 'R'): return (isvd_fun_t) isvd_@x@OrthogonalizeGramian;
    default: fprintf(stderr, "Unknown orthogonalization abbreviation \"%c%c\"!\n", (arg & 0xff), ((arg >> 8) & 0xff));
  }
  return NULL;
}

static inline isvd_fun_t isvd_arg2@x@algi( const int16_t arg ) {
  switch ( arg ) {
    case isvd_char2('K', 'N'): return (isvd_fun_t) isvd_@x@IntegrateKolmogorovNagumo;
    case isvd_char2('W', 'Y'): return (isvd_fun_t) isvd_@x@IntegrateWenYin;
    case isvd_char2('H', 'R'): return (isvd_fun_t) isvd_@x@IntegrateHierarchicalReduction;
    default: fprintf(stderr, "Unknown integration abbreviation \"%c%c\"!\n", (arg & 0xff), ((arg >> 8) & 0xff));
  }
  return NULL;
}

static inline isvd_fun_t isvd_arg2@x@algp( const int16_t arg ) {
  switch ( arg ) {
    case isvd_char2('T', 'S'): return (isvd_fun_t) isvd_@x@PostprocessTallSkinnyQr;
    case isvd_char2('G', 'R'): return (isvd_fun_t) isvd_@x@PostprocessGramian;
    case isvd_char2('S', 'Y'): return (isvd_fun_t) isvd_@x@PostprocessSymmetric;
    default: fprintf(stderr, "Unknown postprocess abbreviation \"%c%c\"!\n", (arg & 0xff), ((arg >> 8) & 0xff));
  }
  return NULL;
}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_CORE_@X@_DRIVER_H_
