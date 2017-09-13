////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/util/mpi.h
/// \brief      The MPI utilities.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef ISVD_UTIL_MPI_H_
#define ISVD_UTIL_MPI_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

mpi_int_t isvd_getMpiSize( const isvd_MpiComm comm );
mpi_int_t isvd_getMpiRank( const isvd_MpiComm comm );

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // ISVD_UTIL_MPI_H_
