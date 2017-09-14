////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/core/driver/@x@_isvd.c
/// \brief      The iSVD driver (@xname@ precision).
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  MIT License
///

#include <isvd/core/@x@_driver.h>
#include <libisvd/def.h>
#include <libisvd/core/@x@_arg.h>
#include <libisvd/util/function.h>
#include <isvd/util/mpi.h>
#include <isvd/util/memory.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup  c_core_@x@_driver_module
/// \brief  General iSVD driver (@xname@ precision).
///
/// \param[in]   alg_s         The selection of sketching algorithm. <br>
///                            `"GP"`: \ref isvd_@x@SketchGaussianProjection "Gaussian Projection sketching".
/// \param[in]   alg_o         The selection of orthogonalization algorithm. <br>
///                            `"TS"`: \ref isvd_@x@OrthogonalizeTallSkinnyQr "Tall Skinny qr orthogonalization". <br>
///                            `"GR"`: \ref isvd_@x@OrthogonalizeGramian "GRamian orthogonalization".
/// \param[in]   alg_i         The selection of integration algorithm. <br>
///                            `"KN"`: \ref isvd_@x@IntegrateKolmogorovNagumo "Kolmogorov-Nagumo integration". <br>
///                            `"WY"`: \ref isvd_@x@IntegrateWenYin "Wen-Yin integration". <br>
///                            `"HR"`: \ref isvd_@x@IntegrateHierarchicalReduction "Hierarchical Reduction integration".
/// \param[in]   alg_p         The selection of postprocessing algorithm. <br>
///                            `"TS"`: \ref isvd_@x@PostprocessTallSkinnyQr "Tall Skinny qr postprocessing". <br>
///                            `"GR"`: \ref isvd_@x@PostprocessGramian "GRamian postprocessing".
/// <hr>
/// \param[in]   m             The number of rows of the matrix 𝑨.
/// \param[in]   n             The number of columns of the matrix 𝑨.
/// \param[in]   k             The desired rank of approximate SVD.
/// \param[in]   p             The oversampling dimension.
/// \param[in]   N             The number of random sketches.
/// <hr>
/// \param[in]   argv, argc    The arguments and their length of each stage. (ignored if \b argv set to `NULL`) <br>
///                            \b argv[0], argc[0]: The sketching arguments and their length. <br>
///                            \b argv[1], argc[1]: The orthogonalization arguments and their length. <br>
///                            \b argv[2], argc[2]: The integration arguments and their length. <br>
///                            \b argv[3], argc[3]: The postprocessing arguments and their length.
/// \param[in]   retv, retc    The return values and their length of each stage. (ignored if \b retv set to `NULL`) <br>
///                            \b retv[0], retc[0]: The sketching return values and their length. <br>
///                            \b retv[1], retc[1]: The orthogonalization return values and their length. <br>
///                            \b retv[2], retc[2]: The integration return values and their length. <br>
///                            \b retv[3], retc[3]: The postprocessing return values and their length.
/// \param[in]   stream        The stream for displaying informations. (disabled if set to `NULL`)
/// <hr>
/// \param[in]   dista         The parallel distribution of 𝑨. <br>
///                            `'C'`: block-column parallelism. <br>
///                            `'R'`: block-row parallelism.
/// \param[in]   ordera        The storage ordering of 𝑨. <br>
///                            `'C'`: column-major ordering. <br>
///                            `'R'`: row-major ordering.
/// \param[in]   a, lda        The column/row-block 𝑨 (\f$m \times n^{(j)}\f$) and its leading dimension. <br>
///                            \b dista = `'C'`: the size must be \f$m \times n^{(j)}\f$. <br>
///                            \b dista = `'R'`: the size must be \f$m^{(j)} \times n\f$.
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
/// \param[out]  retv          Replaced by return values of each stage. (ignored if \b retv set to `NULL`) <br>
///                            \b retv[0]: The sketching return values. <br>
///                            \b retv[1]: The orthogonalization return values. <br>
///                            \b retv[2]: The integration return values. <br>
///                            \b retv[3]: The postprocessing return values.
/// \param[out]  time          Replaced by executing times of each stage. (ignored if \b time set to `NULL`) <br>
///                            \b time[0]: The executing time of sketching stage. <br>
///                            \b time[1]: The executing time of orthogonalization stage. <br>
///                            \b time[2]: The executing time of integration stage. <br>
///                            \b time[3]: The executing time of postprocessing stage.
/// <hr>
/// \param[out]  s             Replaced by the singular values 𝝈.
/// \param[out]  ut            Replaced by the left singular vectors 𝑼 (row-major).
/// \param[out]  vt            Replaced by the right singular vectors 𝑽 (row-major).
///
/// \note  If \b argc ≠ `NULL` and \b argc[i] < 0, then a default argument query is assumed on the i-th stage;
///        the routine only returns the first \b retc[i] default arguments in \b retv[i].
///
/// \see isvd_Param
///
void isvd_@x@Isvd(
    const char         *alg_s,
    const char         *alg_o,
    const char         *alg_i,
    const char         *alg_p,
    const isvd_int_t    m,
    const isvd_int_t    n,
    const isvd_int_t    k,
    const isvd_int_t    p,
    const isvd_int_t    N,
    const @xtype_____@ *argv[4],
    const isvd_int_t    argc[4],
          @xtype_____@ *retv[4],
    const isvd_int_t    retc[4],
          double        time[4],
          FILE        *stream,
    const char          dista,
    const char          ordera,
    const @xtype_____@ *a,
    const isvd_int_t    lda,
          @xtype_____@ *s,
          @xtype_____@ *ut,
    const isvd_int_t    ldut,
          @xtype_____@ *vt,
    const isvd_int_t    ldvt,
    const isvd_int_t    seed,
    const mpi_int_t     ut_root,
    const mpi_int_t     vt_root,
    const mpi_int_t     mpi_root,
    const isvd_MpiComm  mpi_comm
) {

  const mpi_int_t mpi_rank = isvd_getMpiRank(MPI_COMM_WORLD);

  // ====================================================================================================================== //
  // Check arguments

  const char *opts_s[] = {"GP", "GP_gpu"};
  const char *opts_o[] = {"TS", "GR"};
  const char *opts_i[] = {"KN", "WY", "HR"};
  const char *opts_p[] = {"TS", "GR", "SY", "TS_gpu", "GR_gpu", "SY_gpu"};

  const char *alg_s_ = isvd_arg2str("ALG_S", alg_s, opts_s, NULL, lenof(opts_s));
  const char *alg_o_ = isvd_arg2str("ALG_O", alg_o, opts_o, NULL, lenof(opts_o));
  const char *alg_i_ = isvd_arg2str("ALG_I", alg_i, opts_i, NULL, lenof(opts_i));
  const char *alg_p_ = isvd_arg2str("ALG_P", alg_p, opts_p, NULL, lenof(opts_p));
  if ( !alg_s_ || !alg_o_ || !alg_i_ || !alg_p_ ) return;

  isvd_fun_t fun_s = isvd_arg2@x@AlgS(alg_s_);
  isvd_fun_t fun_o = isvd_arg2@x@AlgO(alg_o_);
  isvd_fun_t fun_i = isvd_arg2@x@AlgI(alg_i_);
  isvd_fun_t fun_p = isvd_arg2@x@AlgP(alg_p_);

  // ====================================================================================================================== //
  // Create parameters

  const isvd_Param param = isvd_createParam(m, n, k, p, N, mpi_root, mpi_comm);

  const isvd_int_t mb = param.nrow_each;
  const isvd_int_t l  = param.dim_sketch;
  const isvd_int_t Nl = param.dim_sketch_total;

  // ====================================================================================================================== //
  // Gets arguments and return values of stages

  const @xtype_____@ *argv_s = (argv != NULL) ? argv[0] : NULL;
  const @xtype_____@ *argv_o = (argv != NULL) ? argv[1] : NULL;
  const @xtype_____@ *argv_i = (argv != NULL) ? argv[2] : NULL;
  const @xtype_____@ *argv_p = (argv != NULL) ? argv[3] : NULL;

  const isvd_int_t    argc_s = (argv != NULL) ? argc[0] : 0;
  const isvd_int_t    argc_o = (argv != NULL) ? argc[1] : 0;
  const isvd_int_t    argc_i = (argv != NULL) ? argc[2] : 0;
  const isvd_int_t    argc_p = (argv != NULL) ? argc[3] : 0;

        @xtype_____@ *retv_s = (retv != NULL) ? retv[0] : NULL;
        @xtype_____@ *retv_o = (retv != NULL) ? retv[1] : NULL;
        @xtype_____@ *retv_i = (retv != NULL) ? retv[2] : NULL;
        @xtype_____@ *retv_p = (retv != NULL) ? retv[3] : NULL;

  const isvd_int_t    retc_s = (retv != NULL) ? retc[0] : 0;
  const isvd_int_t    retc_o = (retv != NULL) ? retc[1] : 0;
  const isvd_int_t    retc_i = (retv != NULL) ? retc[2] : 0;
  const isvd_int_t    retc_p = (retv != NULL) ? retc[3] : 0;

  // ====================================================================================================================== //
  // Check stage arguments

  if ( argc_s > 0 ) { isvd_assert_ne(argv_s, nullptr); }
  if ( argc_o > 0 ) { isvd_assert_ne(argv_o, nullptr); }
  if ( argc_i > 0 ) { isvd_assert_ne(argv_i, nullptr); }
  if ( argc_p > 0 ) { isvd_assert_ne(argv_p, nullptr); }
  if ( retc_s > 0 ) { isvd_assert_ne(retv_s, nullptr); }
  if ( retc_o > 0 ) { isvd_assert_ne(retv_o, nullptr); }
  if ( retc_i > 0 ) { isvd_assert_ne(retv_i, nullptr); }
  if ( retc_p > 0 ) { isvd_assert_ne(retv_p, nullptr); }

  // ====================================================================================================================== //
  // Query stage arguments

  bool query = false;
  if ( argc_s < 0 ) {
    fun_s(param, argv_s, argc_s, retv_s, retc_s, dista, ordera, NULL, 1, NULL, 1, seed, mpi_root);
    query = true;
  }
  if ( argc_o < 0 ) {
    fun_o(param, argv_o, argc_o, retv_o, retc_o, NULL, 1);
    query = true;
  }
  if ( argc_i < 0 ) {
    fun_i(param, argv_i, argc_i, retv_i, retc_i, NULL, 1, NULL, 1);
    query = true;
  }
  if ( argc_p < 0 ) {
    fun_p(param, argv_p, argc_p, retv_p, retc_p, dista, ordera, NULL, 1, NULL, 1, NULL, NULL, 1, NULL, 1, ut_root, vt_root);
    query = true;
  }
  if ( query ) {
    return;
  }

  // ====================================================================================================================== //
  // Print arguments

  if ( stream != NULL && mpi_rank == mpi_root ) {
    fprintf(stream, "Using %s\n", isvd_arg2@x@AlgNameS(alg_s_));
    fprintf(stream, "Using %s\n", isvd_arg2@x@AlgNameO(alg_o_));
    fprintf(stream, "Using %s\n", isvd_arg2@x@AlgNameI(alg_i_));
    fprintf(stream, "Using %s\n", isvd_arg2@x@AlgNameP(alg_p_));
    fprintf(stream, "\n");
  }

  // ====================================================================================================================== //
  // Allocate memory

  @xtype_____@ *yst = isvd_@x@malloc(Nl * mb);
  isvd_int_t ldyst = Nl;

  @xtype_____@ *qt = isvd_@x@malloc(l * mb);
  isvd_int_t ldqt = l;

  // ====================================================================================================================== //
  // Run

  if ( stream != NULL && mpi_rank == mpi_root ) { fprintf(stream, "Sketching ...................... "); fflush(stream); }
  double time_s = MPI_Wtime();
  fun_s(param, argv_s, argc_s, retv_s, retc_s, dista, ordera, a, lda, yst, ldyst, seed, mpi_root);
  time_s = MPI_Wtime() - time_s;
  if ( stream != NULL && mpi_rank == mpi_root ) { fprintf(stream, "done\n"); fflush(stream); }

  if ( stream != NULL && mpi_rank == mpi_root ) { fprintf(stream, "Orthogonalizing ................ "); fflush(stream); }
  double time_i = MPI_Wtime();
  fun_o(param, argv_o, argc_o, retv_o, retc_o, yst, ldyst);
  time_i = MPI_Wtime() - time_i;
  if ( stream != NULL && mpi_rank == mpi_root ) { fprintf(stream, "done\n"); fflush(stream); }

  if ( stream != NULL && mpi_rank == mpi_root ) { fprintf(stream, "Integrating .................... "); fflush(stream); }
  double time_o = MPI_Wtime();
  fun_i(param, argv_i, argc_i, retv_i, retc_i, yst, ldyst, qt, ldqt);
  time_o = MPI_Wtime() - time_o;
  if ( stream != NULL && mpi_rank == mpi_root ) { fprintf(stream, "done\n"); fflush(stream); }

  if ( stream != NULL && mpi_rank == mpi_root ) { fprintf(stream, "Postprocessing ................. "); fflush(stream); }
  double time_p = MPI_Wtime();
  fun_p(param, argv_p, argc_p, retv_p, retc_p, dista, ordera, a, lda, qt, ldqt, s, ut, ldut, vt, ldvt, ut_root, vt_root);
  time_p = MPI_Wtime() - time_p;
  if ( stream != NULL && mpi_rank == mpi_root ) { fprintf(stream, "done\n"); fflush(stream); }

  // ====================================================================================================================== //
  // Gets executing times
  if ( time != NULL ) {
    time[0] = time_s;
    time[1] = time_i;
    time[2] = time_o;
    time[3] = time_p;
  }

  // ====================================================================================================================== //
  // Deallocate memory

  isvd_free(yst);
  isvd_free(qt);

}
