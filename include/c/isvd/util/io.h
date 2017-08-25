////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/util/io.h
/// @brief   The I/O utilities.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_UTIL_IO_H_
#define _ISVD_UTIL_IO_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// Get a variable from stream.
///
/// @param   stream  Pointer to a FILE object that identifies an input stream.
///
//@{
static inline void isvd_ifget( FILE *stream, isvd_int_t *varp ) {
#if !defined(ISVD_USE_ILP64)
  isvd_int_t info = fscanf(stream, "%d",  varp);
#else  // ISVD_USE_ILP64
  isvd_int_t info = fscanf(stream, "%ld", varp);
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
//@}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_UTIL_IO_H_
