////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       include/c/isvd/util/mpi.h
/// \brief      The MPI utilities.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#ifndef _ISVD_UTIL_MPI_H_
#define _ISVD_UTIL_MPI_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

mpi_int_t isvd_getMpiSize( const MPI_Comm comm );
mpi_int_t isvd_getMpiRank( const MPI_Comm comm );

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_UTIL_MPI_H_
