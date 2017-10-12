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

void isvd_ifget( FILE *stream, isvd_int_t   *varp );
void isvd_sfget( FILE *stream, isvd_s_val_t *varp );
void isvd_dfget( FILE *stream, isvd_d_val_t *varp );

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_UTIL_IO_H_
