////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/util/mpi.h
/// \brief      The MPI utilities.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef ISVD_UTIL_MPI_H_
#define ISVD_UTIL_MPI_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
#if !defined(ISVD_USE_ILP64)
#define MPI_ISVD_INT_T    MPI_INTEGER4
#else  // ISVD_USE_ILP64
#define MPI_ISVD_INT_T    MPI_INTEGER8
#endif  // ISVD_USE_ILP64
#define MPI_ISVD_S_VAL_T  MPI_REAL4
#define MPI_ISVD_D_VAL_T  MPI_REAL8
#define MPI_ISVD_C_VAL_T  MPI_COMPLEX8
#define MPI_ISVD_Z_VAL_T  MPI_COMPLEX16
#endif  // DOXYGEN_SHOULD_SKIP_THIS

mpi_int_t isvd_getMpiSize( const isvd_MpiComm comm );
mpi_int_t isvd_getMpiRank( const isvd_MpiComm comm );

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_UTIL_MPI_H_
