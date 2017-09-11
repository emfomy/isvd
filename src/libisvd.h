////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd.h
/// \brief      The main library header.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef LIBISVD_H_
#define LIBISVD_H_

#include <libisvd/core.h>
#include <libisvd/la.h>
#include <libisvd/util.h>

#if defined(ISVD_USE_GPU)
  #include <libisvd/gpu.h>
#endif  // ISVD_USE_GPU

#endif  // LIBISVD_H_
