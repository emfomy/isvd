#include <gtest/gtest.h>
#include <mpi.h>
#include <mmio/mmio.h>
#include <isvd.h>

#define YS_PATH ISVD_DATA_PATH "/ys.mtx"
#define QS_PATH ISVD_DATA_PATH "/qs.mtx"

#define serr 1e-3
#define derr 1e-8

typedef @xtype@ isvd_val_t;

TEST(@XStr@GramianOrthogonalization, Test) {

  const mpi_int_t mpi_rank = isvd_getMpiRank(MPI_COMM_WORLD);
  const mpi_int_t mpi_root = 0;

  int m;
  int Nl;

  FILE *file;
  MM_typecode matcode;

  // Read Ys
  file = fopen(YS_PATH, "r");
  ASSERT_NE(file, (void*)(NULL));
  ASSERT_EQ(mm_read_banner(file, &matcode), 0);
  EXPECT_TRUE(mm_is_array(matcode))   << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_real(matcode))    << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_general(matcode)) << mm_typecode_to_str(matcode);
  ASSERT_EQ(mm_read_mtx_array_size(file, &m, &Nl), 0);

  isvd_val_t *yst0 = isvd_@x@malloc(m * Nl);
  isvd_int_t ldyst0 = Nl;
  for ( isvd_int_t ic = 0; ic < Nl; ++ic ) {
    for ( isvd_int_t ir = 0; ir < m; ++ir ) {
      isvd_@x@fget(file, &yst0[ir*ldyst0+ic]);
    }
  }

  if ( file != stdin ) {
    fclose(file);
  }

  // Read Qs
  file = fopen(QS_PATH, "r");
  ASSERT_NE(file, (void*)(NULL));
  ASSERT_EQ(mm_read_banner(file, &matcode), 0);
  EXPECT_TRUE(mm_is_array(matcode))   << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_real(matcode))    << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_general(matcode)) << mm_typecode_to_str(matcode);
  {
    int m_, Nl_;
    ASSERT_EQ(mm_read_mtx_array_size(file, &m_, &Nl_), 0);
    ASSERT_EQ(m_,  m);
    ASSERT_EQ(Nl_, Nl);
  }

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

  // Set parameters
  const isvd_int_t n = m;
  const isvd_int_t k = 11;
  const isvd_int_t p = 0;
  const isvd_int_t l = k+p;
  const isvd_int_t N = Nl / l;
  ASSERT_EQ(Nl % l, 0);

  const isvd_Param param = isvd_createParam(m, n, k, p, N, mpi_root, MPI_COMM_WORLD);

  const isvd_int_t mb  = param.nrow_each;
  const isvd_int_t Pmb = param.nrow_total;

  // Create matrices
  isvd_val_t *yst = yst0 + param.rowidxbegin * ldyst0;
  isvd_int_t ldyst = ldyst0;

  // Run
  isvd_@x@OrthogonalizeGramian(param, NULL, 0, NULL, 0, yst, ldyst);

  // Gather results
  isvd_val_t *qst_ = isvd_@x@malloc(Pmb * Nl);
  isvd_int_t ldqst_ = Nl;
  MPI_Gather(yst, mb*ldyst, MPI_@X_TYPE@, qst_, mb*ldyst, MPI_@X_TYPE@, mpi_root, MPI_COMM_WORLD);

  // Compute space
  isvd_val_t *qqt_ = isvd_@x@malloc(m * m);
  isvd_int_t ldqqt_ = m;
  isvd_val_t *qqt0 = isvd_@x@malloc(m * m);
  isvd_int_t ldqqt0 = m;
  isvd_@x@syrk('U', 'T', m, Nl, 1.0, qst_, ldqst_, 0.0, qqt_, ldqqt_);
  isvd_@x@syrk('U', 'T', m, Nl, 1.0, qst0, ldqst0, 0.0, qqt0, ldqqt0);

  // Check results
  if ( mpi_rank == mpi_root ) {
    for ( isvd_int_t ir = 0; ir < m; ++ir ) {
      for ( isvd_int_t ic = ir; ic < m; ++ic ) {
        ASSERT_NEAR(qqt_[ir+ic*ldqqt_], qqt0[ir+ic*ldqqt0], @x@err) << "(ir, ic) =  (" << ir << ", " << ic << ")";
      }
    }
  }
}
