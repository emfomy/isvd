////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/util/io.h
/// \brief      The I/O utilities.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef ISVD_UTIL_IO_H_
#define ISVD_UTIL_IO_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

@ISVD_TYPE_MACRO_DEFINE@

void isvd_ifget( FILE *stream, INT   *varp );
void isvd_sfget( FILE *stream, REAL4 *varp );
void isvd_dfget( FILE *stream, REAL8 *varp );

@ISVD_TYPE_MACRO_UNDEF@

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_UTIL_IO_H_
