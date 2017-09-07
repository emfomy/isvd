////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/util/io.h
/// \brief      The I/O utilities.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _ISVD_UTIL_IO_H_
#define _ISVD_UTIL_IO_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

void isvd_ifget( FILE *stream, isvd_int_t *varp );
void isvd_sfget( FILE *stream, float *varp );
void isvd_dfget( FILE *stream, double *varp );

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_UTIL_IO_H_
