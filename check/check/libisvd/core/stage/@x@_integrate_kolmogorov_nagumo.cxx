#include <gtest/gtest.h>
#include <mpi.h>
#include <mmio/mmio.h>
#include <isvd.h>

#define QS_PATH ISVD_DATA_PATH "/qs.mtx"
#define Q_PATH  ISVD_DATA_PATH "/q_kn.mtx"

#define tol 1e-4

#define siter 81
#define diter 81

#define serr 1e-3
#define derr 1e-8

typedef @xtype@ isvd_val_t;

TEST(@XStr@KolmogorovNagumoIntegration, Test) {

  const mpi_int_t mpi_rank = isvd_getMpiRank(MPI_COMM_WORLD);
  const mpi_int_t mpi_root = 0;

  int m;
  int l;
  int Nl;

  FILE *file;
  MM_typecode matcode;

  // Read Qs
  file = fopen(QS_PATH, "r");
  ASSERT_NE(file, (void*)(nullptr));
  ASSERT_EQ(mm_read_banner(file, &matcode), 0);
  EXPECT_TRUE(mm_is_array(matcode))   << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_real(matcode))    << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_general(matcode)) << mm_typecode_to_str(matcode);
  ASSERT_EQ(mm_read_mtx_array_size(file, &m, &Nl), 0);

  isvd_val_t *qst0 = isvd_@x@malloc(m * Nl);
  isvd_int_t ldqst0 = Nl;
  for ( isvd_int_t ic = 0; ic < Nl; ++ic ) {
    for ( isvd_int_t ir = 0; ir < m; ++ir ) {
      isvd_@x@fget(file, &qst0[ir*ldqst0+ic]);
    }
  }

  if ( file != stdin ) {
    fclose(file);
  }

  // Read Qbar
  file = fopen(Q_PATH, "r");
  ASSERT_NE(file, (void*)(nullptr));
  ASSERT_EQ(mm_read_banner(file, &matcode), 0);
  EXPECT_TRUE(mm_is_array(matcode))   << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_real(matcode))    << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_general(matcode)) << mm_typecode_to_str(matcode);
  {
    int m_;
    ASSERT_EQ(mm_read_mtx_array_size(file, &m_, &l), 0);
    ASSERT_EQ(m_, m);
  }

  isvd_val_t *qt0 = isvd_@x@malloc(m * l);
  isvd_int_t ldqt0 = l;
  for ( isvd_int_t ic = 0; ic < l; ++ic ) {
    for ( isvd_int_t ir = 0; ir < m; ++ir ) {
      isvd_@x@fget(file, &qt0[ir*ldqt0+ic]);
    }
  }

  if ( file != stdin ) {
    fclose(file);
  }

  // Set parameters
  const isvd_int_t n = m;
  const isvd_int_t k = l;
  const isvd_int_t p = 0;
  const isvd_int_t N = Nl / l;
  ASSERT_EQ(Nl % l, 0);

  const isvd_Param param = isvd_createParam(m, n, k, p, N, mpi_root, MPI_COMM_WORLD);
  const isvd_val_t argv[] = {256, tol};
  const isvd_int_t argc = sizeof(argv) / sizeof(argv[0]);
  const isvd_int_t retc = 1;
        isvd_val_t retv[retc];

  const isvd_int_t mb  = param.nrow_each;
  const isvd_int_t Pmb = param.nrow_total;

  // Create matrices
  isvd_val_t *qst = qst0 + param.rowidxbegin * ldqst0;
  isvd_int_t ldqst = ldqst0;

  isvd_val_t *qt = isvd_@x@malloc(mb * l);
  isvd_int_t ldqt = l;

  // Run stage
  isvd_@x@IntegrateKolmogorovNagumo(param, argv, argc, retv, retc, qst, ldqst, qt, ldqt);
  isvd_int_t iter = retv[0];

  // Gather results
  isvd_val_t *qt_ = isvd_@x@malloc(Pmb * l);
  isvd_int_t ldqt_ = l;
  MPI_Gather(qt, mb*ldqt, MPI_@X_TYPE@, qt_, mb*ldqt, MPI_@X_TYPE@, mpi_root, MPI_COMM_WORLD);

  // Check results
  if ( mpi_rank == mpi_root ) {
    EXPECT_EQ(iter, @x@iter);
    for ( isvd_int_t ir = 0; ir < m; ++ir ) {
      for ( isvd_int_t ic = 0; ic < l; ++ic ) {
        ASSERT_NEAR(qt_[ir*ldqt_+ic], qt0[ir*ldqt0+ic], @x@err) << "(ir, ic) =  (" << ir << ", " << ic << ")";
      }
    }
  }
}
