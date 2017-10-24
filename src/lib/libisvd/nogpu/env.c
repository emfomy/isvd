////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/nogpu/env.c
/// \brief      The iSVD environment routines (NOGPU only).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/gpu/env.h>
#include <libisvd/def.h>
#include <isvd/util/mpi.h>

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

void isvd_init_gpu( int *argcp, char ***argvp, const isvd_MpiComm mpi_comm ) {
  ISVD_UNUSED(argcp);
  ISVD_UNUSED(argvp);
  ISVD_UNUSED(mpi_comm);
}

void isvd_finalize_gpu( void ) {
}

void isvd_printEnvironment_gpu( const isvd_MpiComm mpi_comm ) {
  ISVD_UNUSED(mpi_comm);
  printf("No GPU support\n\n");
}

#endif  // DOXYGEN_SHOULD_SKIP_THIS
