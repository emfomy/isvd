////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/core/@x@_arg.h
/// \brief      The @xname@ precision drivers argument utilities.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef LIBISVD_CORE_@X@_ARG_H_
#define LIBISVD_CORE_@X@_ARG_H_

#include <libisvd/def.h>
#include <isvd/core/@x@_stage.h>
#include <isvd/gpu/@x@_stage.h>
#include <libisvd/util/arg.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

typedef void (*isvd_fun_t)(isvd_Param, ...);

static inline isvd_fun_t isvd_arg2@x@AlgS( const char *arg ) {
  if ( !strcmp(arg, "GP")     ) return (isvd_fun_t) isvd_@x@SketchGaussianProjection;
  if ( !strcmp(arg, "GP_gpu") ) return (isvd_fun_t) isvd_@x@SketchGaussianProjection_gpu;
  fprintf(stderr, "Unknown sketching abbreviation \"%s\"!\n", arg);
  return NULL;
}

static inline isvd_fun_t isvd_arg2@x@AlgO( const char *arg ) {
  if ( !strcmp(arg, "TS")     ) return (isvd_fun_t) isvd_@x@OrthogonalizeTallSkinnyQr;
  if ( !strcmp(arg, "GR")     ) return (isvd_fun_t) isvd_@x@OrthogonalizeGramian;
  fprintf(stderr, "Unknown orthogonalization abbreviation \"%s\"!\n", arg);
  return NULL;
}

static inline isvd_fun_t isvd_arg2@x@AlgI( const char *arg ) {
  if ( !strcmp(arg, "KN")     ) return (isvd_fun_t) isvd_@x@IntegrateKolmogorovNagumo;
  if ( !strcmp(arg, "WY")     ) return (isvd_fun_t) isvd_@x@IntegrateWenYin;
  if ( !strcmp(arg, "MP")     ) return (isvd_fun_t) isvd_@x@IntegrateMultilevelPairwise;
  fprintf(stderr, "Unknown integration abbreviation \"%s\"!\n", arg);
  return NULL;
}

static inline isvd_fun_t isvd_arg2@x@AlgP( const char *arg ) {
  if ( !strcmp(arg, "TS")     ) return (isvd_fun_t) isvd_@x@PostprocessTallSkinnyQr;
  if ( !strcmp(arg, "GR")     ) return (isvd_fun_t) isvd_@x@PostprocessGramian;
  if ( !strcmp(arg, "SY")     ) return (isvd_fun_t) isvd_@x@PostprocessSymmetric;
  if ( !strcmp(arg, "TS_gpu") ) return (isvd_fun_t) isvd_@x@PostprocessTallSkinnyQr_gpu;
  if ( !strcmp(arg, "GR_gpu") ) return (isvd_fun_t) isvd_@x@PostprocessGramian_gpu;
  if ( !strcmp(arg, "SY_gpu") ) return (isvd_fun_t) isvd_@x@PostprocessSymmetric_gpu;
  fprintf(stderr, "Unknown postprocess abbreviation \"%s\"!\n", arg);
  return NULL;
}

static inline const char* isvd_arg2@x@AlgNameS( const char *arg ) {
  if ( !strcmp(arg, "GP")     ) return "@XName@ Precision Gaussian Projection Sketching";
  if ( !strcmp(arg, "GP_gpu") ) return "@XName@ Precision GPU Gaussian Projection Sketching";
  fprintf(stderr, "Unknown sketching abbreviation \"%s\"!\n", arg);
  return NULL;
}

static inline const char* isvd_arg2@x@AlgNameO( const char *arg ) {
  if ( !strcmp(arg, "TS")     ) return "@XName@ Precision Tall-Skinny QR Orthogonalization";
  if ( !strcmp(arg, "GR")     ) return "@XName@ Precision Gramian Orthogonalization";
  fprintf(stderr, "Unknown orthogonalization abbreviation \"%s\"!\n", arg);
  return NULL;
}

static inline const char* isvd_arg2@x@AlgNameI( const char *arg ) {
  if ( !strcmp(arg, "KN")     ) return "@XName@ Precision Kolmogorov-Nagumo Integration";
  if ( !strcmp(arg, "WY")     ) return "@XName@ Precision Wen-Yin Integration";
  if ( !strcmp(arg, "MP")     ) return "@XName@ Precision Multi-level Pairwise Integration";
  fprintf(stderr, "Unknown integration abbreviation \"%s\"!\n", arg);
  return NULL;
}

static inline const char* isvd_arg2@x@AlgNameP( const char *arg ) {
  if ( !strcmp(arg, "TS")     ) return "@XName@ Precision Tall-Skinny QR Postprocessing";
  if ( !strcmp(arg, "GR")     ) return "@XName@ Precision Gramian Postprocessing";
  if ( !strcmp(arg, "SY")     ) return "@XName@ Precision Symmetric Postprocessing";
  if ( !strcmp(arg, "TS_gpu") ) return "@XName@ Precision GPU Tall-Skinny QR Postprocessing";
  if ( !strcmp(arg, "GR_gpu") ) return "@XName@ Precision GPU Gramian Postprocessing";
  if ( !strcmp(arg, "SY_gpu") ) return "@XName@ Precision GPU Symmetric Postprocessing";
  fprintf(stderr, "Unknown postprocess abbreviation \"%s\"!\n", arg);
  return NULL;
}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // LIBISVD_CORE_@X@_ARG_H_
