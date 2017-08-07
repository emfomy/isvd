////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/param.h
/// @brief   The parameters header.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_CORE_PARAM_H_
#define _ISVD_CORE_PARAM_H_

#include <isvd/core/def.h>

inline index_t isvd_param_mb(
    const index_t m, const MPI_Comm mpi_comm
) {
  index_t P; MPI_Comm_size(mpi_comm, &P);
  return (m-1)/P+1;
}

inline index_t isvd_param_nb(
    const index_t n, const MPI_Comm mpi_comm
) {
  index_t P; MPI_Comm_size(mpi_comm, &P);
  return (n-1)/P+1;
}

#endif  // _ISVD_CORE_PARAM_H_
