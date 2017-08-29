////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/core/param.c
/// \brief      The parameter structure.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/core/param.h>
#include <libisvd/def.h>
#include <libisvd/util/mpi.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  core_module
/// Initialize the parameters.
///
isvd_Param isvd_createParam(
    const isvd_int_t nrow,
    const isvd_int_t ncol,
    const isvd_int_t rank,
    const isvd_int_t over_rank,
    const isvd_int_t num_sketch,
    const mpi_int_t  mpi_root,
    const MPI_Comm   mpi_comm
) {

  mpi_int_t mpi_size = isvd_getMpiSize(MPI_COMM_WORLD);
  mpi_int_t mpi_rank = isvd_getMpiRank(MPI_COMM_WORLD);

  struct {
    isvd_int_t nrow_;
    isvd_int_t ncol_;
    isvd_int_t rank_;
    isvd_int_t over_rank_;
    isvd_int_t num_sketch_;
  } args = {nrow, ncol, rank, over_rank, num_sketch};

  MPI_Bcast(&args, sizeof(args), MPI_BYTE, mpi_root, mpi_comm);

  if ( mpi_rank == mpi_root ) {
    isvd_assert_gt(args.nrow_, 0);
    isvd_assert_gt(args.ncol_, 0);
    isvd_assert_gt(args.rank_, 0);
    isvd_assert_ge(args.over_rank_, 0);
    isvd_assert_gt(args.num_sketch_, 0);
    isvd_assert_le(args.nrow_, args.ncol_);
  }

  isvd_int_t nrow_each = (args.nrow_-1) / mpi_size + 1;
  isvd_int_t ncol_each = (args.ncol_-1) / mpi_size + 1;

  isvd_int_t rowidxbegin = mpi_rank * nrow_each;
  isvd_int_t rowidxend   = rowidxbegin + nrow_each;
  isvd_int_t colidxbegin = mpi_rank * ncol_each;
  isvd_int_t colidxend   = colidxbegin + ncol_each;
  if ( rowidxbegin > args.nrow_ ) { rowidxbegin = args.nrow_; }
  if ( rowidxend   > args.nrow_ ) { rowidxend   = args.nrow_; }
  if ( colidxbegin > args.ncol_ ) { colidxbegin = args.ncol_; }
  if ( colidxend   > args.ncol_ ) { colidxend   = args.ncol_; }

  isvd_Param param = {
    .mpi_comm         = mpi_comm,
    .mpi_size         = mpi_size,
    .mpi_rank         = mpi_rank,
    .nrow             = args.nrow_,
    .ncol             = args.ncol_,
    .nrow_proc        = rowidxend - rowidxbegin,
    .ncol_proc        = colidxend - colidxbegin,
    .nrow_each        = nrow_each,
    .ncol_each        = ncol_each,
    .nrow_total       = nrow_each * mpi_size,
    .ncol_total       = ncol_each * mpi_size,
    .rowidxbegin      = rowidxbegin,
    .rowidxend        = rowidxend,
    .colidxbegin      = colidxbegin,
    .colidxend        = colidxend,
    .rank             = args.rank_,
    .over_rank        = args.over_rank_,
    .dim_sketch       = args.rank_ + args.over_rank_,
    .dim_sketch_total = (args.rank_ + args.over_rank_) * args.num_sketch_,
    .num_sketch       = args.num_sketch_
  };

  return param;
}
