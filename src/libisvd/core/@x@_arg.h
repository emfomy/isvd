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
#include <libisvd/util/arg.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

static inline isvd_fun_t isvd_arg2@x@algs( const int16_t arg ) {
  switch ( arg ) {
    case isvd_char2('G', 'P'): return (isvd_fun_t) isvd_@x@SketchGaussianProjection;
    default: fprintf(stderr, "Unknown sketching abbreviation \"%c%c\"!\n", (arg & 0xff), ((arg >> 8) & 0xff));
  }
  return nullptr;
}

static inline isvd_fun_t isvd_arg2@x@algo( const int16_t arg ) {
  switch ( arg ) {
    case isvd_char2('T', 'S'): return (isvd_fun_t) isvd_@x@OrthogonalizeTallSkinnyQr;
    case isvd_char2('G', 'R'): return (isvd_fun_t) isvd_@x@OrthogonalizeGramian;
    default: fprintf(stderr, "Unknown orthogonalization abbreviation \"%c%c\"!\n", (arg & 0xff), ((arg >> 8) & 0xff));
  }
  return nullptr;
}

static inline isvd_fun_t isvd_arg2@x@algi( const int16_t arg ) {
  switch ( arg ) {
    case isvd_char2('K', 'N'): return (isvd_fun_t) isvd_@x@IntegrateKolmogorovNagumo;
    case isvd_char2('W', 'Y'): return (isvd_fun_t) isvd_@x@IntegrateWenYin;
    case isvd_char2('H', 'R'): return (isvd_fun_t) isvd_@x@IntegrateHierarchicalReduction;
    default: fprintf(stderr, "Unknown integration abbreviation \"%c%c\"!\n", (arg & 0xff), ((arg >> 8) & 0xff));
  }
  return nullptr;
}

static inline isvd_fun_t isvd_arg2@x@algp( const int16_t arg ) {
  switch ( arg ) {
    case isvd_char2('T', 'S'): return (isvd_fun_t) isvd_@x@PostprocessTallSkinnyQr;
    case isvd_char2('G', 'R'): return (isvd_fun_t) isvd_@x@PostprocessGramian;
    case isvd_char2('S', 'Y'): return (isvd_fun_t) isvd_@x@PostprocessSymmetric;
    default: fprintf(stderr, "Unknown postprocess abbreviation \"%c%c\"!\n", (arg & 0xff), ((arg >> 8) & 0xff));
  }
  return nullptr;
}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _LIBISVD_CORE_@X@_ARG_H_
