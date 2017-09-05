////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       src/libisvd/core/driver/@x@_isvd.c
/// \brief      The iSVD driver (@xname@ precision).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/core/@x@_driver.h>
#include <libisvd/def.h>
#include <libisvd/core/@x@_arg.h>
#include <libisvd/util/function.h>
#include <libisvd/util/memory.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_@x@_driver_module
/// General iSVD driver (@xname@ precision).
///
/// \param[in]   algs          The selection of sketching algorithm. <br>
///                            `"GP"`: \ref isvd_@x@SketchGaussianProjection "Gaussian Projection sketching".
/// \param[in]   algo          The selection of orthogonalization algorithm. <br>
///                            `"TS"`: \ref isvd_@x@OrthogonalizeTallSkinnyQr "Tall Skinny qr orthogonalization". <br>
///                            `"GR"`: \ref isvd_@x@OrthogonalizeGramian "GRamian orthogonalization".
/// \param[in]   algi          The selection of integration algorithm. <br>
///                            `"KN"`: \ref isvd_@x@IntegrateKolmogorovNagumo "Kolmogorov-Nagumo integration". <br>
///                            `"WY"`: \ref isvd_@x@IntegrateWenYin "Wen-Yin integration". <br>
///                            `"HR"`: \ref isvd_@x@IntegrateHierarchicalReduction "Hierarchical Reduction integration".
/// \param[in]   algp          The selection of postprocessing algorithm. <br>
///                            `"TS"`: \ref isvd_@x@PostprocessTallSkinnyQr "Tall Skinny qr postprocessing". <br>
///                            `"GR"`: \ref isvd_@x@PostprocessGramian "GRamian postprocessing".
/// <hr>
/// \param[in]   m             The number of rows of the matrix 𝑨.
/// \param[in]   n             The number of columns of the matrix 𝑨.
/// \param[in]   k             The desired rank of approximate SVD.
/// \param[in]   p             The oversampling dimension.
/// \param[in]   N             The number of random sketches.
/// <hr>
/// \param[in]   dista         The parallel distribution of 𝑨. <br>
///                            `'C'`: block-column parallelism. <br>
///                            `'R'`: block-row parallelism.
/// \param[in]   ordera        The storage ordering of 𝑨. <br>
///                            `'C'`: column-major ordering. <br>
///                            `'R'`: row-major ordering.
/// \param[in]   a, lda        The column/row-block 𝑨 (\f$m \times n_j\f$) and its leading dimension. <br>
///                            \b dista = `'C'`: the size must be \f$m \times n_j\f$. <br>
///                            \b dista = `'R'`: the size must be \f$m_j \times n\f$.
/// \param[in]   s             The vector 𝝈 (\f$k \times 1\f$).
/// \param[in]   ut, ldut      The matrix 𝑼 (row-major) and its leading dimension. <br>
///                            \b ut_root ≥  0: the size must be \f$Pm_b \times k\f$, and \b ldut must be \f$l\f$. <br>
///                            \b ut_root = -1: the size must be \f$m_b \times k\f$, and \b ldut must be at least \f$l\f$. <br>
///                            \b ut_root < -1: not referenced.
/// \param[in]   vt, ldvt      The matrix 𝑽 (row-major) and its leading dimension. <br>
///                            \b vt_root ≥  0: the size must be \f$Pn_b \times k\f$, and \b ldvt must be \f$l\f$. <br>
///                            \b vt_root = -1: the size must be \f$n_b \times k\f$, and \b ldvt must be at least \f$l\f$. <br>
///                            \b vt_root < -1: not referenced.
/// <hr>
/// \param[in]   seed          The random seed (significant only at MPI process of ID \b mpi_root).
/// \param[in]   ut_root       The option for computing 𝑼. <br>
///                            \b ut_root ≥  0: gather 𝑼 to the MPI process of ID \b ut_root. <br>
///                            \b ut_root = -1: compute row-block 𝑼. <br>
///                            \b ut_root < -1: does not compute 𝑼.
/// \param[in]   vt_root       The option for computing 𝑽. <br>
///                            \b vt_root ≥  0: gather 𝑽 to the MPI process of ID \b vt_root. <br>
///                            \b vt_root = -1: compute row-block 𝑽. <br>
///                            \b vt_root < -1: does not compute 𝑽.
/// \param[in]   mpi_root       The MPI process ID containing the parameters and random seed.
/// \param[in]   mpi_comm      The MPI communicator.
/// <hr>
/// \param[out]  s             Replaced by the singular values 𝝈.
/// \param[out]  ut            Replaced by the left singular vectors 𝑼 (row-major).
/// \param[out]  vt            Replaced by the right singular vectors 𝑽 (row-major).
///
void isvd_@x@Isvd(
    const char       *algs,
    const char       *algo,
    const char       *algi,
    const char       *algp,
    const isvd_int_t  m,
    const isvd_int_t  n,
    const isvd_int_t  k,
    const isvd_int_t  p,
    const isvd_int_t  N,
    const char        dista,
    const char        ordera,
    const @xtype@    *a,
    const isvd_int_t  lda,
          @xtype@    *s,
          @xtype@    *ut,
    const isvd_int_t ldut,
          @xtype@    *vt,
    const isvd_int_t  ldvt,
    const isvd_int_t  seed,
    const mpi_int_t   ut_root,
    const mpi_int_t   vt_root,
    const mpi_int_t   mpi_root,
    const MPI_Comm    mpi_comm
) {

  // ====================================================================================================================== //
  // Check arguments

  const char *optss[] = {"GP", "GP_gpu"};
  const char *optso[] = {"TS", "GR"};
  const char *optsi[] = {"KN", "WY", "HR"};
  const char *optsp[] = {"TS", "GR", "TS_gpu", "GR_gpu"};

  const char *algs_ = isvd_arg2str("ALGS", algs, optss, nullptr, lenof(optss));
  const char *algo_ = isvd_arg2str("ALGO", algo, optso, nullptr, lenof(optso));
  const char *algi_ = isvd_arg2str("ALGI", algi, optsi, nullptr, lenof(optsi));
  const char *algp_ = isvd_arg2str("ALGP", algp, optsp, nullptr, lenof(optsp));
  if ( !algs_ || !algo_ || !algi_ || !algp_ ) return;

  isvd_fun_t funs = isvd_arg2@x@algs(algs_);
  isvd_fun_t funo = isvd_arg2@x@algo(algo_);
  isvd_fun_t funi = isvd_arg2@x@algi(algi_);
  isvd_fun_t funp = isvd_arg2@x@algp(algp_);

  // ====================================================================================================================== //
  // Create parameters

  const isvd_Param param = isvd_createParam(m, n, k, p, N, mpi_root, mpi_comm);

  const isvd_int_t mb = param.nrow_each;
  const isvd_int_t l  = param.dim_sketch;
  const isvd_int_t Nl = param.dim_sketch_total;

  // ====================================================================================================================== //
  // Allocate memory

  @xtype@ *yst = isvd_@x@malloc(mb * Nl);
  isvd_int_t ldyst = Nl;

  @xtype@ *qt = isvd_@x@malloc(mb * l);
  isvd_int_t ldqt = l;

  // ====================================================================================================================== //
  // Run

  funs(param, nullptr, 0, nullptr, 0, dista, ordera, a, lda, yst, ldyst, seed, mpi_root);
  funo(param, nullptr, 0, nullptr, 0, yst, ldyst);
  funi(param, nullptr, 0, nullptr, 0, yst, ldyst, qt, ldqt);
  funp(param, nullptr, 0, nullptr, 0, dista, ordera, a, lda, qt, ldqt, s, ut, ldut, vt, ldvt, ut_root, vt_root);

}
