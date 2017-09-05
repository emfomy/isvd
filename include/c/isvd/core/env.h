////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/core/env.h
/// \brief      The iSVD environment routines.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _ISVD_CORE_ENV_H_
#define _ISVD_CORE_ENV_H_

#include <isvd/def.h>
#include <isvd/gpu/env.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

void isvd_init_cpu( int *argcp, char ***argvp, const MPI_Comm mpi_comm );
void isvd_finalize_cpu( void );
void isvd_printEnvironment_cpu( const MPI_Comm comm );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_module
/// Initializes the iSVD environment.
///
/// \note  This routines initializes the MPI and MAGMA environments.
///
static inline void isvd_init( int *argcp, char ***argvp, const MPI_Comm mpi_comm ) {
  isvd_init_cpu(argcp, argvp, mpi_comm);
  isvd_init_gpu(argcp, argvp, mpi_comm);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_module
/// Finalizes the iSVD environment.
///
/// \note  This routines initializes the MPI and MAGMA environments.
///
static inline void isvd_finalize() {
  isvd_finalize_cpu();
  isvd_finalize_gpu();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_module
/// Displays the iSVD environment.
///
/// \note  This routines displays the MPI and MAGMA environments.
///
static inline void isvd_printEnvironment( const MPI_Comm mpi_comm ) {
  isvd_printEnvironment_cpu(mpi_comm);
  isvd_printEnvironment_gpu(mpi_comm);
}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_CORE_ENV_H_
