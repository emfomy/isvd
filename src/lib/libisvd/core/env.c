////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/core/env.c
/// \brief      The iSVD environment routines (CPU only).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/core/env.h>
#include <libisvd/def.h>
#include <isvd/util/mpi.h>
#include <isvd/util/omp.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_module
/// \brief  Initializes the iSVD environment (CPU only).
///
/// \note  This routines initializes the MPI environment.
///
void isvd_Init_cpu( int *argcp, char ***argvp, const isvd_MpiComm mpi_comm ) {
  ISVD_UNUSED(mpi_comm);
  MPI_Init(argcp, argvp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_module
/// \brief  Finalizes the iSVD environment (CPU only).
///
/// \note  This routines initializes the MPI environment.
///
void isvd_Finalize_cpu( void ) {
  MPI_Finalize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_module
/// \brief  Displays the iSVD environment (CPU only).
///
/// \note  This routines displays the MPI environment.
///
void isvd_PrintEnvironment_cpu( const isvd_MpiComm mpi_comm ) {
  mpi_int_t mpi_size = isvd_getMpiSize(mpi_comm);
  omp_int_t omp_size = isvd_getOmpMaxSize();

  printf("iSVD %s, %lu-bit isvd_int_t, %lu-bit pointer.\n", ISVD_VERSION, sizeof(isvd_int_t) * 8, sizeof(void*) * 8);
  printf("%d MPI processors, %d OpenMP threads per process.\n\n", mpi_size, omp_size);
}
