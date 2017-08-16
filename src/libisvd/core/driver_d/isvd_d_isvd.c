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
/// @param[in]   algs          The selection of sketching algorithms.
/// @param[in]   algo          The selection of orthogonalization algorithms.
/// @param[in]   algi          The selection of integration algorithms.
/// @param[in]   algp          The selection of postprocessing algorithms.
/// <hr>
/// @param[in]   m             The number of rows of the matrix 𝑨.
/// @param[in]   n             The number of rows of the matrix 𝑨.
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
/// @param[in]   seed          The random seed (significant only at MPI process of ID `seed_root`).
/// @param[in]   seed_root     The MPI process ID containing the random seed.
/// @param[in]   ut_root       The option for computing 𝑼. <br>
///                            `ut_root >= 0`: gather 𝑼 to the MPI process of ID `ut_root`. <br>
///                            `ut_root = -1`: compute row-block 𝑼. <br>
///                            `ut_root < -1`: does not compute 𝑼.
/// @param[in]   vt_root       The option for computing 𝑽. <br>
///                            `vt_root >= 0`: gather 𝑽 to the MPI process of ID `vt_root`. <br>
///                            `vt_root = -1`: compute row-block 𝑽. <br>
///                            `vt_root < -1`: does not compute 𝑽.
/// @param[in]   mpi_comm      The MPI communicator.
/// <hr>
/// @param[out]  retvs         Replaced by the sketching return values.
/// @param[out]  retvo         Replaced by the orthogonalization return values.
/// @param[out]  retvi         Replaced by the integration return values.
/// @param[out]  retvp         Replaced by the postprocessing return values.
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
    const mpi_int_t seed_root,
    const mpi_int_t ut_root,
    const mpi_int_t vt_root,
    const MPI_Comm mpi_comm
) {

  // ====================================================================================================================== //
  // Check arguments

  int16_t algs_ = isvd_arg2char2("ALGS", algs, "GP");
  int16_t algo_ = isvd_arg2char2("ALGO", algo, "TSGR");
  int16_t algi_ = isvd_arg2char2("ALGI", algi, "KNWYHR");
  int16_t algp_ = isvd_arg2char2("ALGP", algp, "TSGRSY");
  if ( !algs_ || !algo_ || !algi_ || !algp_ ) return;

}
