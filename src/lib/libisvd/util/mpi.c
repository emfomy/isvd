////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/util/mpi.c
/// \brief      The MPI utilities.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/util/mpi.h>
#include <libisvd/def.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_util_mpi_module
/// \brief  Returns the size of the group associated with a communicator.
///
/// \param  comm  The communicator.
///
/// \return       The number of processes in the group of \a comm.
///
mpi_int_t isvd_getMpiSize( const isvd_MpiComm comm ) {
  mpi_int_t size; isvd_assert_pass(MPI_Comm_size(comm, &size)); return size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_util_mpi_module
/// \brief  Determines the rank of the calling process in the communicator.
///
/// \param  comm  The communicator.
///
/// \return       The rank of the calling process in group of \a comm.
///
mpi_int_t isvd_getMpiRank( const isvd_MpiComm comm ) {
  mpi_int_t rank; isvd_assert_pass(MPI_Comm_rank(comm, &rank)); return rank;
}
