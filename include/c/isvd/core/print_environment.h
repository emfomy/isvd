////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/core/print_environment.h
/// \brief      Display the iSVD environment.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _ISVD_CORE_PRINT_ENVIRONMENT_H_
#define _ISVD_CORE_PRINT_ENVIRONMENT_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

void isvd_printEnvironment( const MPI_Comm comm, const mpi_int_t mpi_root );

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_CORE_PRINT_ENVIRONMENT_H_
