////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/core/@x@_arg.h
/// \brief      The @xname@ precision drivers argument utilities.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _LIBISVD_CORE_@X@_ARG_H_
#define _LIBISVD_CORE_@X@_ARG_H_

#include <libisvd/def.h>
#include <isvd/core/@x@_stage.h>
#include <isvd/gpu/@x@_stage.h>
#include <libisvd/util/arg.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

typedef void (*isvd_fun_t)(isvd_Param, ...);

static inline isvd_fun_t isvd_arg2@x@algs( const char *arg ) {
  if      ( !strcmp(arg, "GP")     ) return (isvd_fun_t) isvd_@x@SketchGaussianProjection;
  if      ( !strcmp(arg, "GP_gpu") ) return (isvd_fun_t) isvd_@x@SketchGaussianProjection_gpu;
  else fprintf(stderr, "Unknown sketching abbreviation \"%s\"!\n", arg); return nullptr;
}

static inline isvd_fun_t isvd_arg2@x@algo( const char *arg ) {
  if      ( !strcmp(arg, "TS")     ) return (isvd_fun_t) isvd_@x@OrthogonalizeTallSkinnyQr;
  else if ( !strcmp(arg, "GR")     ) return (isvd_fun_t) isvd_@x@OrthogonalizeGramian;
  else fprintf(stderr, "Unknown orthogonalization abbreviation \"%s\"!\n", arg); return nullptr;
}

static inline isvd_fun_t isvd_arg2@x@algi( const char *arg ) {
  if      ( !strcmp(arg, "KN")     ) return (isvd_fun_t) isvd_@x@IntegrateKolmogorovNagumo;
  else if ( !strcmp(arg, "WY")     ) return (isvd_fun_t) isvd_@x@IntegrateWenYin;
  else if ( !strcmp(arg, "HR")     ) return (isvd_fun_t) isvd_@x@IntegrateHierarchicalReduction;
  else fprintf(stderr, "Unknown integration abbreviation \"%s\"!\n", arg); return nullptr;
}

static inline isvd_fun_t isvd_arg2@x@algp( const char *arg ) {
  if      ( !strcmp(arg, "TS")     ) return (isvd_fun_t) isvd_@x@PostprocessTallSkinnyQr;
  else if ( !strcmp(arg, "GR")     ) return (isvd_fun_t) isvd_@x@PostprocessGramian;
  else if ( !strcmp(arg, "SY")     ) return (isvd_fun_t) isvd_@x@PostprocessSymmetric;
  else if ( !strcmp(arg, "TS_gpu") ) return (isvd_fun_t) isvd_@x@PostprocessTallSkinnyQr_gpu;
  else if ( !strcmp(arg, "GR_gpu") ) return (isvd_fun_t) isvd_@x@PostprocessGramian_gpu;
  else if ( !strcmp(arg, "SY_gpu") ) return (isvd_fun_t) isvd_@x@PostprocessSymmetric_gpu;
  else fprintf(stderr, "Unknown postprocess abbreviation \"%s\"!\n", arg); return nullptr;
}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _LIBISVD_CORE_@X@_ARG_H_
