////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/util/io.h
/// \brief      The I/O utilities.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _LIBISVD_UTIL_IO_H_
#define _LIBISVD_UTIL_IO_H_

#include <libisvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  utility_module
/// Get a variable from stream.
///
/// \param  stream  Pointer to a FILE object that identifies an input stream.
/// \param  varp    Pointer to the variable.
///
//\{
static inline void isvd_ifget( FILE *stream, isvd_int_t *varp ) {
#if !defined(ISVD_USE_ILP64)
  isvd_int_t info = fscanf(stream, "%"PRId32,  varp);
#else  // ISVD_USE_ILP64
  isvd_int_t info = fscanf(stream, "%"PRId64, varp);
#endif  // ISVD_USE_ILP64
  ISVD_UNUSED(info);
  isvd_assert_eq(info, 1);
}

static inline void isvd_sfget( FILE *stream, float *varp ) {
  isvd_int_t info = fscanf(stream, "%f",  varp);
  ISVD_UNUSED(info);
  isvd_assert_eq(info, 1);
}

static inline void isvd_dfget( FILE *stream, double *varp ) {
  isvd_int_t info = fscanf(stream, "%lf", varp);
  ISVD_UNUSED(info);
  isvd_assert_eq(info, 1);
}
//\}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _LIBISVD_UTIL_IO_H_
