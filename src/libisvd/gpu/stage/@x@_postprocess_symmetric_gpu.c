////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/gpu/stage/@x@_postprocess_symmetric_gpu.c
/// \brief      The GPU Symmetric Postprocessing (@xname@ precision)
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/gpu/@x@_stage.h>
#include <libisvd/gpu/def.h>
#include <isvd/la.h>
#include <libisvd/gpu/stage/@x@_postprocess_gpu.h>
#include <libisvd/util/arg.h>
#include <libisvd/util/memory.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_gpu_@x@_stage_module
/// GPU Symmetric Postprocessing (@xname@ precision)
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
/// \param[in]   ut_root     The option for computing 𝑼. <br>
///                          \b ut_root ≥  0: gather 𝑼 to the MPI process of ID \b ut_root. <br>
///                          \b ut_root = -1: compute row-block 𝑼. <br>
///                          \b ut_root < -1: does not compute 𝑼.
/// <hr>
/// \param[out]  s           Replaced by the singular values 𝝈.
/// \param[out]  ut          Replaced by the left singular vectors 𝑼 (row-major).
///
/// \attention  Set \ref isvd_gpu_memory_limit as the limit of GPU memory usage.
///
void isvd_@x@PostprocessSymmetric_gpu(
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
    const mpi_int_t   ut_root
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

  isvd_assert_eq(mj, nj);
  isvd_assert_eq(mb, nb);

  if ( ut_root >= 0 ) {
    isvd_assert_eq(ldut, l);
  } else if ( ut_root == -1 ) {
    isvd_assert_ge(ldut, l);
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
    case 'C': projectBlockCol_gpu(param, ordera_, a, lda, qt, ldqt, zt, ldzt, s, ut, ldut, ut_root); break;
    case 'R': projectBlockRow_gpu(param, ordera_, a, lda, qt, ldqt, zt, ldzt, s, ut, ldut, ut_root); break;
    default:  isvd_assert_fail();
  }

  // ====================================================================================================================== //
  // Compute eigen-decomposition

  // W := Z' * Q
  isvd_@x@Gemmt('U', 'N', 'T', l, nj, 1.0, zt, ldzt, qt, ldqt, 0.0, w, ldw);
  MPI_Allreduce(MPI_IN_PLACE, w, ldw*l, MPI_@X_TYPE@, MPI_SUM, param.mpi_comm);

  // eig(W) = W * S * W'
  const char jobw_ = (ut_root >= -1) ? 'V' : 'N';
  isvd_@x@Syev(jobw_, 'U', l, w, ldw, s);

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

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_free(zt);
  isvd_free(w);

}
