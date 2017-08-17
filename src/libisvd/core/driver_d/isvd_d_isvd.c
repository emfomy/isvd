////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    src/libisvd/core/driver_d/isvd_d_isvd.c
/// @brief   The iSVD driver (double precision)
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <isvd/core/driver_d.h>
#include <isvd/util/memory.h>

typedef double isvd_val_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  core_driver_d_module
/// iSVD driver (double precision)
///
/// @param[in]   algs          The selection of sketching algorithm. <br>
///                            `"GP"`: @ref isvd_dSketchGaussianProjection "Gaussian Projection sketching".
/// @param[in]   algo          The selection of orthogonalization algorithm. <br>
///                            `"TS"`: @ref isvd_dOrthogonalizeTallSkinnyQr "Tall Skinny qr orthogonalization". <br>
///                            `"GR"`: @ref isvd_dOrthogonalizeGramian "GRamian orthogonalization".
/// @param[in]   algi          The selection of integration algorithm. <br>
///                            `"KN"`: @ref isvd_dIntegrateKolmogorovNagumo "Kolmogorov-Nagumo integration". <br>
///                            `"WY"`: @ref isvd_dIntegrateWenYin "Wen-Yin integration". <br>
///                            `"HR"`: @ref isvd_dIntegrateHierarchicalReduction "Hierarchical Reduction integration".
/// @param[in]   algp          The selection of postprocessing algorithm. <br>
///                            `"TS"`: @ref isvd_dPostprocessTallSkinnyQr "Tall Skinny qr postprocessing". <br>
///                            `"GR"`: @ref isvd_dPostprocessGramian "GRamian postprocessing".
/// <hr>
/// @param[in]   m             The number of rows of the matrix 𝑨.
/// @param[in]   n             The number of columns of the matrix 𝑨.
/// @param[in]   k             The desired rank of approximate SVD.
/// @param[in]   p             The oversampling dimension.
/// @param[in]   N             The number of random sketches.
/// <hr>
/// @param[in]   dista         The parallel distribution of 𝑨. <br>
///                            `'C'`: block-column parallelism. <br>
///                            `'R'`: block-row parallelism.
/// @param[in]   ordera        The storage ordering of 𝑨. <br>
///                            `'C'`: column-major ordering. <br>
///                            `'R'`: row-major ordering.
/// @param[in]   a, lda        The column/row-block 𝑨 (@f$m \times n_j@f$) and its leading dimension. <br>
///                            `dista='C'`: the size must be @f$m \times n_j@f$. <br>
///                            `dista='R'`: the size must be @f$m_j \times n@f$.
/// @param[in]   s             The vector 𝝈 (@f$k \times 1@f$).
/// @param[in]   ut, ldut      The matrix 𝑼 (row-major) and its leading dimension. <br>
///                            `ut_root >= 0`: the size must be @f$Pm_b \times k@f$, and @p ldut must be @f$l@f$. <br>
///                            `ut_root = -1`: the size must be @f$m_b \times k@f$, and @p ldut must be at least @f$l@f$. <br>
///                            `ut_root < -1`: not referenced.
/// @param[in]   vt, ldvt      The matrix 𝑽 (row-major) and its leading dimension. <br>
///                            `vt_root >= 0`: the size must be @f$Pn_b \times k@f$, and @p ldvt must be @f$l@f$. <br>
///                            `vt_root = -1`: the size must be @f$n_b \times k@f$, and @p ldvt must be at least @f$l@f$. <br>
///                            `vt_root < -1`: not referenced.
/// <hr>
/// @param[in]   seed          The random seed (significant only at MPI process of ID `mpi_root`).
/// @param[in]   ut_root       The option for computing 𝑼. <br>
///                            `ut_root >= 0`: gather 𝑼 to the MPI process of ID `ut_root`. <br>
///                            `ut_root = -1`: compute row-block 𝑼. <br>
///                            `ut_root < -1`: does not compute 𝑼.
/// @param[in]   vt_root       The option for computing 𝑽. <br>
///                            `vt_root >= 0`: gather 𝑽 to the MPI process of ID `vt_root`. <br>
///                            `vt_root = -1`: compute row-block 𝑽. <br>
///                            `vt_root < -1`: does not compute 𝑽.
/// @param[in]   mpi_root       The MPI process ID containing the parameters and random seed.
/// @param[in]   mpi_comm      The MPI communicator.
/// <hr>
/// @param[out]  s             Replaced by the singular values 𝝈.
/// @param[out]  ut            Replaced by the left singular vectors 𝑼 (row-major).
/// @param[out]  vt            Replaced by the right singular vectors 𝑽 (row-major).
///
void isvd_dIsvd(
    const char *algs,
    const char *algo,
    const char *algi,
    const char *algp,
    const isvd_int_t m,
    const isvd_int_t n,
    const isvd_int_t k,
    const isvd_int_t p,
    const isvd_int_t N,
    const char dista,
    const char ordera,
    const isvd_val_t *a,
    const isvd_int_t lda,
          isvd_val_t *s,
          isvd_val_t *ut,
    const isvd_int_t ldut,
          isvd_val_t *vt,
    const isvd_int_t ldvt,
    const isvd_int_t seed,
    const mpi_int_t ut_root,
    const mpi_int_t vt_root,
    const mpi_int_t mpi_root,
    const MPI_Comm mpi_comm
) {

  // ====================================================================================================================== //
  // Check arguments

  const int16_t algs_ = isvd_arg2char2("ALGS", algs, "GP");
  const int16_t algo_ = isvd_arg2char2("ALGO", algo, "TSGR");
  const int16_t algi_ = isvd_arg2char2("ALGI", algi, "KNWYHR");
  const int16_t algp_ = isvd_arg2char2("ALGP", algp, "TSGR");
  if ( !algs_ || !algo_ || !algi_ || !algp_ ) return;

  isvd_fun_t funs = isvd_arg2algs(algs_);
  isvd_fun_t funo = isvd_arg2algo(algo_);
  isvd_fun_t funi = isvd_arg2algi(algi_);
  isvd_fun_t funp = isvd_arg2algp(algp_);

  // ====================================================================================================================== //
  // Create parameters

  const isvd_Param param = isvd_createParam(m, n, k, p, N, mpi_root, mpi_comm);

  const isvd_int_t mb = param.nrow_each;
  const isvd_int_t l  = param.dim_sketch;
  const isvd_int_t Nl = param.dim_sketch_total;

  // ====================================================================================================================== //
  // Allocate memory

  isvd_val_t *yst = isvd_dmalloc(mb * Nl);
  isvd_int_t ldyst = Nl;

  isvd_val_t *qt = isvd_dmalloc(mb * l);
  isvd_int_t ldqt = l;

  // ====================================================================================================================== //
  // Run

  funs(param, NULL, 0, NULL, 0, dista, ordera, a, lda, yst, ldyst, seed, mpi_root);
  funo(param, NULL, 0, NULL, 0, yst, ldyst);
  funi(param, NULL, 0, NULL, 0, yst, ldyst, qt, ldqt);
  funp(param, NULL, 0, NULL, 0, dista, ordera, a, lda, qt, ldqt, s, ut, ldut, vt, ldvt, ut_root, vt_root);

}
