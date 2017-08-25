////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/util/mpi.h
/// @brief   The MPI utilities.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_UTIL_MPI_H_
#define _ISVD_UTIL_MPI_H_

#include <isvd/def.h>

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  util_module
/// @brief  Returns the size of the group associated with a communicator.
///
/// @param  comm  The communicator.
///
/// @return       The number of processes in the group of @a comm.
///
static inline mpi_int_t isvd_getMpiSize( const MPI_Comm comm ) {
  mpi_int_t size; isvd_assert_pass(MPI_Comm_size(comm, &size)); return size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  util_module
/// @brief  Determines the rank of the calling process in the communicator.
///
/// @param  comm  The communicator.
///
/// @return       The rank of the calling process in group of @a comm.
///
static inline mpi_int_t isvd_getMpiRank( const MPI_Comm comm ) {
  mpi_int_t rank; isvd_assert_pass(MPI_Comm_rank(comm, &rank)); return rank;
}

#define MPI_COMPLEX_FLOAT  MPI_COMPLEX8
#define MPI_COMPLEX_DOUBLE MPI_COMPLEX16

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // _ISVD_UTIL_MPI_H_
