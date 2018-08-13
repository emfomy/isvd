////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/core/stage/@x@_postprocess_gramian.c
/// \brief      The Gramian Postprocessing (@xname@ precision).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017 Mu Yang. All rights reserved.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#include <isvd/core/@x@_stage.h>
#include <libisvd/def.h>
#include <isvd/la.h>
#include <libisvd/core/stage/@x@_postprocess.h>
#include <libisvd/util/arg.h>
#include <isvd/util/memory.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_stage_module
/// \brief  Gramian Postprocessing (@xname@ precision).
///
/// \param[in]   param       The \ref isvd_Param "parameters".
/// \param[in]   argv, argc  The arguments and its length. (not using)
/// \param[in]   retv, retc  The return values and its length. (not using)
/// <hr>
/// \param[in]   dista       The parallel distribution of 𝑨. <br>
///                          \c 'C': block-column parallelism. <br>
///                          \c 'R': block-row parallelism.
/// \param[in]   ordera      The storage ordering of 𝑨. <br>
///                          \c 'C': column-major ordering. <br>
///                          \c 'R': row-major ordering.
/// \param[in]   a, lda      The column/row-block 𝑨 (\f$m \times n^{(j)}\f$) and its leading dimension. <br>
///                          \b dista = \c 'C': the size must be \f$m \times n^{(j)}\f$. <br>
///                          \b dista = \c 'R': the size must be \f$m^{(j)} \times n\f$.
/// \param[in]   qt, ldqt    The row-block 𝑸 (\f$ m_b \times l \f$, row-major) and its leading dimension.
/// \param[in]   s           The vector 𝝈 (\f$k \times 1\f$).
/// \param[in]   ut, ldut    The matrix 𝑼 (row-major) and its leading dimension. <br>
///                          \b ut_root ≥  0: the size must be \f$Pm_b \times k\f$ in the root process,
///                                           and be \f$m_b \times k\f$ in other processes. \b ldut must be \f$l\f$. <br>
///                          \b ut_root = -1: the size must be \f$m_b \times k\f$, and \b ldut must be at least \f$l\f$. <br>
///                          \b ut_root < -1: not referenced.
/// \param[in]   vt, ldvt    The matrix 𝑽 (row-major) and its leading dimension. <br>
///                          \b vt_root ≥  0: the size must be \f$Pn_b \times k\f$ in the root process,
///                                           and be \f$n_b \times k\f$ in other processes. \b ldvt must be \f$l\f$. <br>
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
/// \param[out]  s           Replaced by the singular values 𝝈 in descending order.
/// \param[out]  ut          Replaced by the left singular vectors 𝑼 (row-major).
/// \param[out]  vt          Replaced by the right singular vectors 𝑽 (row-major).
///
/// \note  If \b argc < 0, then a default argument query is assumed;
///        the routine only returns the first \b retc default arguments in \b retv.
///
/// \see isvd_Param, \ref tutorial_core_notation
///
void isvd_@x@PostprocessGramian(
    const isvd_Param    param,
    const @xtype_____@ *argv,
    const isvd_int_t    argc,
          @xtype_____@ *retv,
    const isvd_int_t    retc,
    const char          dista,
    const char          ordera,
    const @xtype_____@ *a,
    const isvd_int_t    lda,
    const @xtype_____@ *qt,
    const isvd_int_t    ldqt,
          @xtype_____@ *s,
          @xtype_____@ *ut,
    const isvd_int_t    ldut,
          @xtype_____@ *vt,
    const isvd_int_t    ldvt,
    const mpi_int_t     ut_root,
    const mpi_int_t     vt_root
) {

  ISVD_UNUSED(argv);
  ISVD_UNUSED(retv);

  if ( argc > 0 ) { isvd_assert_ne(argv, nullptr); }
  if ( retc > 0 ) { isvd_assert_ne(retv, nullptr); }
  if ( argc < 0 ) return;

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

  const char dista_  = isvd_arg2char("DISTA",  dista,  "CR", NULL);
  const char ordera_ = isvd_arg2char("ORDERA", ordera, "CR", NULL);
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

  // matrix Z'
  @xtype_____@ *zt = isvd_@x@Malloc(l * nb);
  isvd_int_t ldzt = l;

  // matrix W
  @xtype_____@ *w = isvd_@x@Malloc(l * l);
  isvd_int_t ldw = l;

  // ====================================================================================================================== //
  // Projection

  switch ( dista_ ) {
    case 'C': projectBlockCol(param, ordera_, a, lda, qt, ldqt, zt, ldzt, s, ut, ldut, ut_root); break;
    case 'R': projectBlockRow(param, ordera_, a, lda, qt, ldqt, zt, ldzt, s, vt, ldvt, vt_root); break;
    default:  isvd_assert_fail();
  }

  // ====================================================================================================================== //
  // Compute eigen-decomposition

  // W := Z' * Z
  isvd_@x@Gemm('N', 'T', l, l, nj, 1.0, zt, ldzt, zt, ldzt, 0.0, w, ldw);
  isvd_assert_pass(MPI_Allreduce(MPI_IN_PLACE, w, ldw*l, MPI_@XTYPE@, MPI_SUM, param.mpi_comm));

  // eig(W) = W * S^2 * W'
  const char jobw_ = (ut_root >= -1 || vt_root >= -1) ? 'O' : 'N';
  isvd_@x@Gesvd(jobw_, 'N', l, l, w, ldw, s, NULL, 1, NULL, 1);
  isvd_v@x@Sqrt(l, s, s);

  // ====================================================================================================================== //
  // Compute singular vectors

  // U := Q * W (U' := W' * Q')
  if ( ut_root >= -1 ) {
    isvd_@x@Gemm('T', 'N', k, mj, l, 1.0, w, ldw, qt, ldqt, 0.0, ut, ldut);

    if ( ut_root >= 0 ) {
      if ( param.mpi_rank == ut_root ) {
        isvd_assert_pass(MPI_Gather(MPI_IN_PLACE, mb*ldut, MPI_@XTYPE@,
                                    ut, mb*ldut, MPI_@XTYPE@, ut_root, param.mpi_comm));
      } else {
        isvd_assert_pass(MPI_Gather(ut, mb*ldut, MPI_@XTYPE@,
                                    NULL, mb*ldut, MPI_@XTYPE@, ut_root, param.mpi_comm));
      }
    }
  }

  // V := Z * W / S (V' := (W / S)' * Z')
  if ( vt_root >= -1 ) {
    isvd_@x@Dism('R', l, k, 1.0, s, w, ldw);
    isvd_@x@Gemm('T', 'N', k, nj, l, 1.0, w, ldw, zt, ldzt, 0.0, vt, ldvt);

    if ( vt_root >= 0 ) {
      if ( param.mpi_rank == vt_root ) {
        isvd_assert_pass(MPI_Gather(MPI_IN_PLACE, nb*ldvt, MPI_@XTYPE@,
                                    vt, nb*ldvt, MPI_@XTYPE@, vt_root, param.mpi_comm));
      } else {
        isvd_assert_pass(MPI_Gather(vt, nb*ldvt, MPI_@XTYPE@,
                                    NULL, nb*ldvt, MPI_@XTYPE@, vt_root, param.mpi_comm));
      }
    }
  }

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_Free(zt);
  isvd_Free(w);

}
