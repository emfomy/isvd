////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/la/vsl/service.h
/// \brief      The VSL service header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef ISVD_LA_VSL_SERVICE_H_
#define ISVD_LA_VSL_SERVICE_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

typedef isvd_int_t* isvd_VSLStreamStatePtr;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_vsl_service_module
/// \brief  Creates and initializes a random stream.
void isvd_vslNewStream( isvd_VSLStreamStatePtr *streamp, const isvd_int_t seed );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_vsl_service_module
/// \brief  Deletes previously created stream.
void isvd_vslDeleteStream( isvd_VSLStreamStatePtr *streamp );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_la_vsl_service_module
/// \brief  Initializes the stream by the skip-ahead method.
void isvd_vslSkipAheadStream( isvd_VSLStreamStatePtr stream, const isvd_int_t nskip );

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_LA_VSL_SERVICE_H_
