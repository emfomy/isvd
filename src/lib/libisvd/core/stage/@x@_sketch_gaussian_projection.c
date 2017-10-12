////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/core/stage/@x@_sketch_gaussian_projection.c
/// \brief      The Gaussian Projection Sketching (@xname@ precision).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/core/@x@_stage.h>
#include <libisvd/def.h>
#include <isvd/la.h>
#include <libisvd/core/stage/@x@_sketch.h>
#include <libisvd/util/arg.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_@x@_stage_module
/// \brief  Gaussian Projection Sketching (@xname@ precision).
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
/// \param[in]   a, lda      The column/row-block 𝑨 (\f$m \times n^{(j)}\f$) and its leading dimension. <br>
///                          \b dista = `'C'`: the size must be \f$m \times n^{(j)}\f$. <br>
///                          \b dista = `'R'`: the size must be \f$m^{(j)} \times n\f$.
/// \param[in]   yst, ldyst  The row-block 𝖄 (\f$m_b \times Nl\f$, row-major) and its leading dimension. <br>
///                          \b dista = `'C'`: \b ldyst must be \f$Nl\f$. <br>
///                          \b dista = `'R'`: no condition.
/// \param[in]   seed        The random seed (significant only at root MPI process).
/// \param[in]   mpi_root    The root MPI process ID.
/// <hr>
/// \param[out]  yst         Replaced by the row-block 𝖄 (row-major).
///
/// \note  If \b argc < 0, then a default argument query is assumed;
///        the routine only returns the first \b retc default arguments in \b retv.
///
/// \see isvd_Param, \ref tutorial_core_notation
///
void isvd_@x@SketchGaussianProjection(
    const isvd_Param    param,
    const @xtype_____@ *argv,
    const isvd_int_t    argc,
          @xtype_____@ *retv,
    const isvd_int_t    retc,
    const char          dista,
    const char          ordera,
    const @xtype_____@ *a,
    const isvd_int_t    lda,
          @xtype_____@ *yst,
    const isvd_int_t    ldyst,
    const isvd_int_t    seed,
    const mpi_int_t     mpi_root
) {

  ISVD_UNUSED(argv);
  ISVD_UNUSED(retv);

  if ( argc > 0 ) { isvd_assert_ne(argv, nullptr); }
  if ( retc > 0 ) { isvd_assert_ne(retv, nullptr); }
  if ( argc < 0 ) return;

  // ====================================================================================================================== //
  // Check arguments

  const char dista_  = isvd_arg2char("DISTA",  dista,  "CR", NULL);
  const char ordera_ = isvd_arg2char("ORDERA", ordera, "CR", NULL);
  if ( !dista_ || !ordera_ ) return;

  // ====================================================================================================================== //
  // Run

  switch ( dista_ ) {
    case 'C': sketchBlockCol(param, ordera_, a, lda, yst, ldyst, seed, mpi_root); break;
    case 'R': sketchBlockRow(param, ordera_, a, lda, yst, ldyst, seed, mpi_root); break;
    default:  isvd_assert_fail();
  }
}
