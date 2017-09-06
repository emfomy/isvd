////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd.h
/// \brief      The main library header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _LIBISVD_H_
#define _LIBISVD_H_

#include <libisvd/def.h>
#include <libisvd/core.h>
#include <libisvd/util.h>

#if defined(ISVD_USE_GPU)
  #include <libisvd/gpu.h>
#endif  // ISVD_USE_GPU

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \defgroup  src_util_module  Development Utility
/// \ingroup   src_module
/// \brief     The Development Utility
///

#endif  // _LIBISVD_H_
