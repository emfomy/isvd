////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/core/env.h
/// \brief      The iSVD environment routines.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef ISVD_CORE_ENV_H_
#define ISVD_CORE_ENV_H_

#include <isvd/def.h>
#include <isvd/gpu/env.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

void isvd_Init_cpu( int *argcp, char ***argvp, const isvd_MpiComm mpi_comm );
void isvd_Finalize_cpu( void );
void isvd_PrintEnvironment_cpu( const isvd_MpiComm comm );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_module
/// \brief  Initializes the iSVD environment.
///
/// \note  This routines initializes the MPI and MAGMA environments.
///
static inline void isvd_Init( int *argcp, char ***argvp, const isvd_MpiComm mpi_comm ) {
  isvd_Init_cpu(argcp, argvp, mpi_comm);
  isvd_Init_gpu(argcp, argvp, mpi_comm);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_module
/// \brief  Finalizes the iSVD environment.
///
/// \note  This routines initializes the MPI and MAGMA environments.
///
static inline void isvd_Finalize() {
  isvd_Finalize_cpu();
  isvd_Finalize_gpu();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_module
/// \brief  Displays the iSVD environment.
///
/// \note  This routines displays the MPI and MAGMA environments.
///
static inline void isvd_PrintEnvironment( const isvd_MpiComm mpi_comm ) {
  isvd_PrintEnvironment_cpu(mpi_comm);
  isvd_PrintEnvironment_gpu(mpi_comm);
}

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_CORE_ENV_H_
