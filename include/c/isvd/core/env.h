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

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

void isvd_init(     int *argcp, char ***argvp, const MPI_Comm mpi_comm );
void isvd_init_cpu( int *argcp, char ***argvp, const MPI_Comm mpi_comm );

void isvd_finalize(     void );
void isvd_finalize_cpu( void );

void isvd_printEnvironment(     const MPI_Comm comm );
void isvd_printEnvironment_cpu( const MPI_Comm comm );

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_CORE_ENV_H_
