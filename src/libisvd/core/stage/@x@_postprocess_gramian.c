////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/core/stage/@x@_postprocess_gramian.c
/// \brief      The Gramian Postprocessing (@xname@ precision)
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/core/@x@_stage.h>
#include <libisvd/def.h>
#include <libisvd/la.h>
#include <libisvd/util/arg.h>
#include <libisvd/util/memory.h>

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
static void projectBlockCol(
    const isvd_Param  param,
    const char        ordera,
    const @xtype@    *a,
    const isvd_int_t  lda,
    const @xtype@    *qt,
    const isvd_int_t  ldqt,
          @xtype@    *zt,
    const isvd_int_t  ldzt,
          @xtype@    *s,
          @xtype@    *ut,
    const isvd_int_t  ldut,
          @xtype@    *vt,
    const isvd_int_t  ldvt,
    const mpi_int_t   ut_root,
    const mpi_int_t   vt_root
) {

  ISVD_UNUSED(s);
  ISVD_UNUSED(vt);
  ISVD_UNUSED(ldut);
  ISVD_UNUSED(ldvt);
  ISVD_UNUSED(vt_root);

  // ====================================================================================================================== //
  // Get parameters

  const isvd_int_t m   = param.nrow;
  const isvd_int_t mb  = param.nrow_each;
  const isvd_int_t Pmb = param.nrow_total;
  const isvd_int_t nj  = param.ncol_proc;
  const isvd_int_t l   = param.dim_sketch;

  // ====================================================================================================================== //
  // Check arguments

  const bool use_ut = (ut_root >= 0);

  switch ( ordera ) {
    case 'C': isvd_assert_ge(lda, m);  break;
    case 'R': isvd_assert_ge(lda, nj); break;
    default:  isvd_assert_fail();
  }
  isvd_assert_eq(ldqt, l);
  isvd_assert_ge(ldzt, l);
  if ( use_ut ) {
    isvd_assert_eq(ldut, l);
  }

  // ====================================================================================================================== //
  // Allocate memory

  @xtype@ *qt_;
  if ( use_ut ) {
    qt_ = ut;
  } else {
    qt_ = isvd_@x@malloc(Pmb * l);
  }
  isvd_int_t ldqt_ = l;

  // ====================================================================================================================== //
  // Rearrange

  MPI_Allgather(qt, mb*ldqt, MPI_@X_TYPE@, qt_, mb*ldqt, MPI_@X_TYPE@, param.mpi_comm);

  // ====================================================================================================================== //
  // Project

  // Z := A' * Q (Z' := Q' * A)
  char transa_ = (ordera == 'C') ? 'N' : 'T';
  isvd_@x@Gemm('N', transa_, l, nj, m, 1.0, qt_, ldqt_, a, lda, 0.0, zt, ldzt);

  // ====================================================================================================================== //
  // Deallocate memory

  if ( !use_ut ) {
    isvd_free(qt_);
  }

}

static void projectBlockRow(
    const isvd_Param  param,
    const char        ordera,
    const @xtype@    *a,
    const isvd_int_t  lda,
    const @xtype@    *qt,
    const isvd_int_t  ldqt,
          @xtype@    *zt,
    const isvd_int_t  ldzt,
          @xtype@    *s,
          @xtype@    *ut,
    const isvd_int_t  ldut,
          @xtype@    *vt,
    const isvd_int_t  ldvt,
    const mpi_int_t   ut_root,
    const mpi_int_t   vt_root
) {

  ISVD_UNUSED(s);
  ISVD_UNUSED(ut);
  ISVD_UNUSED(ldut);
  ISVD_UNUSED(ldvt);
  ISVD_UNUSED(ut_root);

  // ====================================================================================================================== //
  // Get parameters

  const isvd_int_t mj  = param.nrow_proc;
  const isvd_int_t n   = param.ncol;
  const isvd_int_t nb  = param.ncol_each;
  const isvd_int_t Pnb = param.ncol_total;
  const isvd_int_t l   = param.dim_sketch;

  // ====================================================================================================================== //
  // Check arguments

  const bool use_vt = (vt_root >= 0);

  switch ( ordera ) {
    case 'C': isvd_assert_ge(lda, mj); break;
    case 'R': isvd_assert_ge(lda, n);  break;
    default:  isvd_assert_fail();
  }
  isvd_assert_ge(ldqt, l);
  isvd_assert_eq(ldzt, l);
  if ( use_vt ) {
    isvd_assert_eq(ldvt, l);
  }

  // ====================================================================================================================== //
  // Allocate memory

  @xtype@ *zt_;
  if ( use_vt ) {
    zt_ = vt;
  } else {
    zt_ = isvd_@x@malloc(Pnb * l);
  }
  isvd_int_t ldzt_ = l;

  // ====================================================================================================================== //
  // Project

  // Z := A' * Q (Z' := Q' * A)
  char transa_ = (ordera == 'C') ? 'N' : 'T';
  isvd_@x@Gemm('N', transa_, l, n, mj, 1.0, qt, ldqt, a, lda, 0.0, zt_, ldzt_);

  // ====================================================================================================================== //
  // Rearrange

  MPI_Reduce_scatter_block(zt_, zt, nb*ldzt, MPI_@X_TYPE@, MPI_SUM, param.mpi_comm);

  // ====================================================================================================================== //
  // Deallocate memory

  if ( !use_vt ) {
    isvd_free(zt_);
  }

}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_@x@_stage_module
/// Gramian Postprocessing (@xname@ precision)
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
/// \param[in]   qt, ldqt    The row-block 𝑸 (\f$ m_b \times l \f$, row-major) and its leading dimension.
/// \param[in]   s           The vector 𝝈 (\f$k \times 1\f$).
/// \param[in]   ut, ldut    The matrix 𝑼 (row-major) and its leading dimension. <br>
///                          \b ut_root ≥  0: the size must be \f$Pm_b \times k\f$, and \b ldut must be \f$l\f$. <br>
///                          \b ut_root = -1: the size must be \f$m_b \times k\f$, and \b ldut must be at least \f$l\f$. <br>
///                          \b ut_root < -1: not referenced.
/// \param[in]   vt, ldvt    The matrix 𝑽 (row-major) and its leading dimension. <br>
///                          \b vt_root ≥  0: the size must be \f$Pn_b \times k\f$, and \b ldvt must be \f$l\f$. <br>
///                          \b vt_root = -1: the size must be \f$n_b \times k\f$, and \b ldvt must be at least \f$l\f$. <br>
///                          \b vt_root < -1: not referenced.
/// \param[in]   ut_root     The option for computing 𝑼. <br>
///                          \b ut_root ≥  0: gather 𝑼 to the MPI process of ID \b ut_root. <br>
///                          \b ut_root = -1: compute row-block 𝑼. <br>
///                          \b ut_root < -1: does not compute 𝑼.
/// \param[in]   vt_root     The option for computing 𝑽. <br>
///                          \b vt_root ≥  0: gather 𝑽 to the MPI process of ID \b vt_root. <br>
///                          \b vt_root = -1: compute row-block 𝑽. <br>
///                          \b vt_root < -1: does not compute 𝑽.
/// <hr>
/// \param[out]  s           Replaced by the singular values 𝝈.
/// \param[out]  ut          Replaced by the left singular vectors 𝑼 (row-major).
/// \param[out]  vt          Replaced by the right singular vectors 𝑽 (row-major).
///
void isvd_@x@PostprocessGramian(
    const isvd_Param  param,
    const @xtype@    *argv,
    const isvd_int_t  argc,
          @xtype@    *retv,
    const isvd_int_t  retc,
    const char        dista,
    const char        ordera,
    const @xtype@    *a,
    const isvd_int_t  lda,
    const @xtype@    *qt,
    const isvd_int_t  ldqt,
          @xtype@    *s,
          @xtype@    *ut,
    const isvd_int_t  ldut,
          @xtype@    *vt,
    const isvd_int_t  ldvt,
    const mpi_int_t   ut_root,
    const mpi_int_t   vt_root
) {

  ISVD_UNUSED(argv);
  ISVD_UNUSED(argc);
  ISVD_UNUSED(retv);
  ISVD_UNUSED(retc);

  // ====================================================================================================================== //
  // Get parameters

  const isvd_int_t mj = param.nrow_proc;
  const isvd_int_t mb = param.nrow_each;
  const isvd_int_t nj = param.ncol_proc;
  const isvd_int_t nb = param.ncol_each;
  const isvd_int_t k  = param.rank;
  const isvd_int_t l  = param.dim_sketch;

  // ====================================================================================================================== //
  // Check arguments

  const char dista_  = isvd_arg2char("DISTA",  dista,  "CR", nullptr);
  const char ordera_ = isvd_arg2char("ORDERA", ordera, "CR", nullptr);
  if ( !dista_ || !ordera_ ) return;

  if ( ut_root >= 0 ) {
    isvd_assert_eq(ldut, l);
  } else if ( ut_root == -1 ) {
    isvd_assert_ge(ldut, l);
  }

  if ( vt_root >= 0 ) {
    isvd_assert_eq(ldvt, l);
  } else if ( vt_root == -1 ) {
    isvd_assert_ge(ldvt, l);
  }

  // ====================================================================================================================== //
  // Allocate memory

  @xtype@ *zt = isvd_@x@malloc(nb * l);
  isvd_int_t ldzt = l;

  @xtype@ *w = isvd_@x@malloc(l * l);
  isvd_int_t ldw = l;

  // ====================================================================================================================== //
  // Projection

  switch ( dista_ ) {
    case 'C': projectBlockCol(param, ordera_, a, lda, qt, ldqt, zt, ldzt, s, ut, ldut, vt, ldvt, ut_root, vt_root); break;
    case 'R': projectBlockRow(param, ordera_, a, lda, qt, ldqt, zt, ldzt, s, ut, ldut, vt, ldvt, ut_root, vt_root); break;
    default:  isvd_assert_fail();
  }

  // ====================================================================================================================== //
  // Compute eigen-decomposition

  // W := Z' * Z
  isvd_@x@Gemm('N', 'T', l, l, nj, 1.0, zt, ldzt, zt, ldzt, 0.0, w, ldw);
  MPI_Allreduce(MPI_IN_PLACE, w, ldw*l, MPI_@X_TYPE@, MPI_SUM, param.mpi_comm);

  // eig(W) = W * S^2 * W'
  const char jobw_ = (ut_root >= -1 || vt_root >= -1) ? 'O' : 'N';
  isvd_@x@Gesvd(jobw_, 'N', l, l, w, ldw, s, nullptr, 1, nullptr, 1);
  isvd_v@x@Sqrt(l, s, s);

  // ====================================================================================================================== //
  // Compute singular vectors

  // U := Q * W (U' := W' * Q')
  if ( ut_root >= -1 ) {
    isvd_@x@Gemm('T', 'N', k, mj, k, 1.0, w, ldw, qt, ldqt, 0.0, ut, ldut);

    if ( ut_root >= 0 ) {
      if ( param.mpi_rank == ut_root ) {
        MPI_Gather(MPI_IN_PLACE, mb*ldut, MPI_@X_TYPE@, ut, mb*ldut, MPI_@X_TYPE@, ut_root, param.mpi_comm);
      } else {
        MPI_Gather(ut, mb*ldut, MPI_@X_TYPE@, nullptr, mb*ldut, MPI_@X_TYPE@, ut_root, param.mpi_comm);
      }
    }
  }

  // V := Z * W / S (V' := (W / S)' * Z')
  if ( vt_root >= -1 ) {
    for ( isvd_int_t ii = 0; ii < l; ++ii ) {
      isvd_@x@Scal(l, 1.0/s[ii], w + ii*ldw, 1);
    }
    isvd_@x@Gemm('T', 'N', k, nj, k, 1.0, w, ldw, zt, ldzt, 0.0, vt, ldvt);

    if ( vt_root >= 0 ) {
      if ( param.mpi_rank == vt_root ) {
        MPI_Gather(MPI_IN_PLACE, nb*ldvt, MPI_@X_TYPE@, vt, nb*ldvt, MPI_@X_TYPE@, vt_root, param.mpi_comm);
      } else {
        MPI_Gather(vt, nb*ldvt, MPI_@X_TYPE@, nullptr, nb*ldvt, MPI_@X_TYPE@, vt_root, param.mpi_comm);
      }
    }
  }

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_free(zt);
  isvd_free(w);

}
