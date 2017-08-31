////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/vsl/service.h
/// \brief      The VSL service header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _ISVD_LA_VSL_SERVICE_H_
#define _ISVD_LA_VSL_SERVICE_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

@ISVD_LA_BLAS_TYPE_DEFINE@

typedef INT* isvd_VSLStreamStatePtr;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_vsl_module
/// Creates and initializes a random stream.
void isvd_vslNewStream( isvd_VSLStreamStatePtr *streamp, const INT seed );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_vsl_module
/// Deletes previously created stream.
void isvd_vslDeleteStream( isvd_VSLStreamStatePtr *streamp );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_vsl_module
/// Initializes the stream by the skip-ahead method.
void isvd_vslSkipAheadStream( isvd_VSLStreamStatePtr stream, const INT nskip );

@ISVD_LA_BLAS_TYPE_UNDEF@

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_LA_VSL_SERVICE_H_
