////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/core/stage/@x@_sketch_gaussian_projection.c
/// \brief      The Gaussian Projection Sketching (@xname@ precision)
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/core/@x@_stage.h>
#include <isvd/la.h>
#include <isvd/util/arg.h>
#include <isvd/util/memory.h>
#include <isvd/util/omp.h>

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
static void sketchBlockCol(
    const isvd_Param  param,
    const char        ordera,
    const @xtype@    *a,
    const isvd_int_t  lda,
          @xtype@    *yst,
    const isvd_int_t  ldyst,
    const isvd_int_t  seed,
    const mpi_int_t   mpi_root
) {

  ISVD_UNUSED(ldyst);

  // ====================================================================================================================== //
  // Get parameters

  const isvd_int_t m   = param.nrow;
  const isvd_int_t mb  = param.nrow_each;
  const isvd_int_t Pmb = param.nrow_total;
  const isvd_int_t nj  = param.ncol_proc;
  const isvd_int_t nb  = param.ncol_each;
  const isvd_int_t Nl  = param.dim_sketch_total;

  // ====================================================================================================================== //
  // Check arguments

  switch ( ordera ) {
    case 'C': isvd_assert_ge(lda, m);  break;
    case 'R': isvd_assert_ge(lda, nj); break;
  }
  isvd_assert_eq(ldyst, Nl);

  // ====================================================================================================================== //
  // Allocate memory

  @xtype@ *omegat = isvd_@x@malloc(nj * Nl);
  isvd_int_t ldomegat = Nl;

  @xtype@ *yst_ = isvd_@x@malloc(Pmb * Nl);
  isvd_int_t ldyst_ = Nl;

  // ====================================================================================================================== //
  // Random generate

  isvd_int_t seed_ = seed;
  MPI_Bcast(&seed_, sizeof(seed_), MPI_BYTE, mpi_root, param.mpi_comm);


  ISVD_OMP_PARALLEL
  {
    omp_int_t omp_size = isvd_getOmpSize();
    omp_int_t omp_rank = isvd_getOmpRank();

    isvd_int_t len   = nj * Nl / omp_size;
    isvd_int_t start = len * omp_rank;
    if ( omp_rank == omp_size-1 ) {
      len = nj * Nl - start;
    }

    isvd_VSLStreamStatePtr stream;
    isvd_vslNewStream(&stream, seed_);
    isvd_vslSkipAheadStream(stream, (nb * Nl * param.mpi_rank + start) * 2);
    isvd_v@x@RngGaussian(stream, len, omegat + start, 0.0, 1.0);

    isvd_vslDeleteStream(&stream);
  }

  // ====================================================================================================================== //
  // Project

  // Yi := A * Omegai (Yi' := Omegai' * A')
  char transa_ = (ordera == 'C') ? 'T' : 'N';
  isvd_@x@gemm('N', transa_, Nl, m, nj, 1.0, omegat, ldomegat, a, lda, 0.0, yst_, ldyst_);

  // ====================================================================================================================== //
  // Rearrange

  MPI_Reduce_scatter_block(yst_, yst, mb*ldyst_, MPI_@X_TYPE@, MPI_SUM, param.mpi_comm);

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_free(omegat);

}

static void sketchBlockRow(
    const isvd_Param  param,
    const char        ordera,
    const @xtype@    *a,
    const isvd_int_t  lda,
          @xtype@    *yst,
    const isvd_int_t  ldyst,
    const isvd_int_t  seed,
    const mpi_int_t   mpi_root
) {

  // ====================================================================================================================== //
  // Get parameters

  const isvd_int_t mj = param.nrow_proc;
  const isvd_int_t n  = param.ncol;
  const isvd_int_t Nl = param.dim_sketch_total;

  // ====================================================================================================================== //
  // Check arguments

  switch ( ordera ) {
    case 'C': isvd_assert_ge(lda, mj); break;
    case 'R': isvd_assert_ge(lda, n);  break;
  }
  isvd_assert_ge(ldyst, Nl);

  // ====================================================================================================================== //
  // Allocate memory

  @xtype@ *omegat = isvd_@x@malloc(n * Nl);
  isvd_int_t ldomegat = Nl;

  // ====================================================================================================================== //
  // Random generate

  isvd_int_t seed_ = seed;
  MPI_Bcast(&seed_, sizeof(isvd_VSLStreamStatePtr), MPI_BYTE, mpi_root, param.mpi_comm);

  ISVD_OMP_PARALLEL
  {
    omp_int_t omp_size = isvd_getOmpSize();
    omp_int_t omp_rank = isvd_getOmpRank();

    isvd_int_t len   = n * Nl / omp_size;
    isvd_int_t start = len * omp_rank;
    if ( omp_rank == omp_size-1 ) {
      len = n * Nl - start;
    }

    isvd_VSLStreamStatePtr stream;
    isvd_vslNewStream(&stream, seed_);
    isvd_vslSkipAheadStream(stream, start * 2);
    isvd_v@x@RngGaussian(stream, len, omegat + start, 0.0, 1.0);

    isvd_vslDeleteStream(&stream);
  }

  // ====================================================================================================================== //
  // Project

  // Yi := A * Omegai (Yi' := Omegai' * A')
  char transa_ = (ordera == 'C') ? 'T' : 'N';
  isvd_@x@gemm('N', transa_, Nl, mj, n, 1.0, omegat, ldomegat, a, lda, 0.0, yst, ldyst);

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_free(omegat);

}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  core_@x@_stage_module
/// Gaussian Projection Sketching (@xname@ precision)
///
/// \param[in]   param       The \ref isvd_Param "parameters".
/// \param[in]   argv, argc  The arguments and its length. (not using)
/// \param[in]   retv, retc  The return values and its length. (not using)
/// <hr>
/// \param[in]   dista       The parallel distribution of 𝑨. <br>
///                          `'C'`: block-column parallelism. <br>
///                          `'R'`: block-row parallelism.
/// \param[in]   ordera      The storage ordering of 𝑨. <br>
///                          `'C'`: column-major ordering. <br>
///                          `'R'`: row-major ordering.
/// \param[in]   a, lda      The column/row-block 𝑨 (\f$m \times n_j\f$) and its leading dimension. <br>
///                          \b dista = `'C'`: the size must be \f$m \times n_j\f$. <br>
///                          \b dista = `'R'`: the size must be \f$m_j \times n\f$.
/// \param[in]   yst, ldyst  The row-block 𝖄 (\f$m_b \times Nl\f$, row-major) and its leading dimension. <br>
///                          \b dista = `'C'`: \b ldyst must be \f$Nl\f$. <br>
///                          \b dista = `'R'`: no condition.
/// \param[in]   seed        The random seed (significant only at root MPI process).
/// \param[in]   mpi_root    The root MPI process ID.
/// <hr>
/// \param[out]  yst         Replaced by the row-block 𝖄 (row-major).
///
void isvd_@x@SketchGaussianProjection(
    const isvd_Param  param,
    const @xtype@    *argv,
    const isvd_int_t  argc,
          @xtype@    *retv,
    const isvd_int_t  retc,
    const char        dista,
    const char        ordera,
    const @xtype@    *a,
    const isvd_int_t  lda,
          @xtype@    *yst,
    const isvd_int_t  ldyst,
    const isvd_int_t  seed,
    const mpi_int_t   mpi_root
) {

  ISVD_UNUSED(argv);
  ISVD_UNUSED(argc);
  ISVD_UNUSED(retv);
  ISVD_UNUSED(retc);

  // ====================================================================================================================== //
  // Check arguments

  const char dista_  = isvd_arg2char("DISTA",  dista,  "CR", nullptr);
  const char ordera_ = isvd_arg2char("ORDERA", ordera, "CR", nullptr);
  if ( !dista_ || !ordera_ ) return;

  // ====================================================================================================================== //
  // Run

  switch ( dista_ ) {
    case 'C': sketchBlockCol(param, ordera_, a, lda, yst, ldyst, seed, mpi_root); break;
    case 'R': sketchBlockRow(param, ordera_, a, lda, yst, ldyst, seed, mpi_root); break;
  }
}
