////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/nogpu/env.c
/// \brief      The iSVD environment routines (NOGPU only).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/gpu/env.h>
#include <libisvd/def.h>
#include <libisvd/util/mpi.h>

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

void isvd_init_gpu( int *argcp, char ***argvp, const MPI_Comm mpi_comm ) {
  ISVD_UNUSED(argcp);
  ISVD_UNUSED(argvp);
  ISVD_UNUSED(mpi_comm);
}

void isvd_finalize_gpu( void ) {
}

void isvd_printEnvironment_gpu( const MPI_Comm mpi_comm ) {
  ISVD_UNUSED(mpi_comm);
  printf("No GPU support\n\n");
}

#endif  // DOXYGEN_SHOULD_SKIP_THIS
