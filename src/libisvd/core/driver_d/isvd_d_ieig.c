////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    src/libisvd/core/driver_d/isvd_d_ieig.c
/// @brief   The iEig driver (double precision)
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <isvd/core/driver_d.h>
#include <isvd/util/memory.h>

typedef double isvd_val_t;

static void dummy() { fprintf(stderr, "Not implemented!\n"); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  core_driver_d_module
/// iEig driver (double precision)
///
/// @param[in]   algs          The selection of sketching algorithms.
/// @param[in]   algo          The selection of orthogonalization algorithms.
/// @param[in]   algi          The selection of integration algorithms.
/// @param[in]   algp          The selection of postprocessing algorithms.
/// <hr>
/// @param[in]   m             The number of rows of the matrix 𝑨.
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
/// <hr>
/// @param[in]   seed          The random seed (significant only at MPI process of ID `mpi_root`).
/// @param[in]   ut_root       The option for computing 𝑼. <br>
///                            `ut_root >= 0`: gather 𝑼 to the MPI process of ID `ut_root`. <br>
///                            `ut_root = -1`: compute row-block 𝑼. <br>
///                            `ut_root < -1`: does not compute 𝑼.
/// @param[in]   mpi_root       The MPI process ID containing the parameters and random seed.
/// @param[in]   mpi_comm      The MPI communicator.
/// <hr>
/// @param[out]  retvs         Replaced by the sketching return values.
/// @param[out]  retvo         Replaced by the orthogonalization return values.
/// @param[out]  retvi         Replaced by the integration return values.
/// @param[out]  retvp         Replaced by the postprocessing return values.
/// @param[out]  s             Replaced by the eigenvalues 𝝈.
/// @param[out]  ut            Replaced by the left eigenvectors 𝑼 (row-major).
///
void isvd_dIeig(
    const char *algs,
    const char *algo,
    const char *algi,
    const char *algp,
    const isvd_int_t m,
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
    const isvd_int_t seed,
    const mpi_int_t ut_root,
    const mpi_int_t mpi_root,
    const MPI_Comm mpi_comm
) {

  // ====================================================================================================================== //
  // Check arguments

  const int16_t algs_ = isvd_arg2char2("ALGS", algs, "GP");
  const int16_t algo_ = isvd_arg2char2("ALGO", algo, "TSGR");
  const int16_t algi_ = isvd_arg2char2("ALGI", algi, "KNWYHR");
  const int16_t algp_ = isvd_arg2char2("ALGP", algp, "SY");
  if ( !algs_ || !algo_ || !algi_ || !algp_ ) return;

  // ====================================================================================================================== //
  // Select stage

  typedef void (*fun_t)(isvd_Param, ...);

  fun_t funs = (fun_t) dummy;
  switch ( algs_ ) {
    case isvd_char2('G', 'P'): funs = (fun_t) isvd_dSketchGaussianProjection; break;
  }

  fun_t funo = (fun_t) dummy;
  switch ( algo_ ) {
    // case isvd_char2('T', 'S'): funo = (fun_t) isvd_dOrthogonalizeTallSkinnyQr; break;
    case isvd_char2('G', 'R'): funo = (fun_t) isvd_dOrthogonalizeGramian; break;
  }

  fun_t funi = (fun_t) dummy;
  switch ( algi_ ) {
    case isvd_char2('K', 'N'): funi = (fun_t) isvd_dIntegrateKolmogorovNagumo; break;
    // case isvd_char2('W', 'Y'): funi = (fun_t) isvd_dIntegrateWenYin; break;
  }

  fun_t funp = (fun_t) dummy;
  switch ( algp_ ) {
    // case isvd_char2('T', 'S'): funp = (fun_t) isvd_dPostprocessTallSkinnyQr; break;
    case isvd_char2('G', 'R'): funp = (fun_t) isvd_dPostprocessGramian; break;
  }

  // ====================================================================================================================== //
  // Create parameters

  const isvd_int_t n  = m;
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
  funp(param, NULL, 0, NULL, 0, dista, ordera, a, lda, qt, ldqt, s, ut, ldut, ut_root);

}
