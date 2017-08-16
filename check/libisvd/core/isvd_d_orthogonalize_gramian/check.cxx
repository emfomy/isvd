#include <gtest/gtest.h>
#include <mpi.h>
#include <mmio/mmio.h>
#include <isvd.h>

#define YS_PATH ISVD_DATA_PATH "/ys.mtx"
#define QS_PATH ISVD_DATA_PATH "/qs.mtx"

typedef double isvd_val_t;

TEST(GramianOrthogonalization, Test) {

  const mpi_int_t mpi_rank = isvd_getMpiRank(MPI_COMM_WORLD);
  const mpi_int_t mpi_root = 0;

  isvd_int_t m;
  isvd_int_t Nl;

  FILE *file;
  MM_typecode matcode;

  // Reads Ys
  file = fopen(YS_PATH, "r");
  ASSERT_NE(file, (void*)(NULL));
  ASSERT_EQ(mm_read_banner(file, &matcode), 0);
  EXPECT_TRUE(mm_is_array(matcode))   << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_real(matcode))    << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_general(matcode)) << mm_typecode_to_str(matcode);
  ASSERT_EQ(mm_read_mtx_array_size(file, &m, &Nl), 0);

  isvd_val_t *yst0 = isvd_dmalloc(m * Nl);
  isvd_int_t ldyst0 = Nl;
  for ( isvd_int_t ic = 0; ic < Nl; ++ic ) {
    for ( isvd_int_t ir = 0; ir < m; ++ir ) {
      EXPECT_EQ(fscanf(file, "%lg", &yst0[ir*ldyst0+ic]), 1);
    }
  }

  if ( file != stdin ) {
    fclose(file);
  }

  // Reads Qs
  file = fopen(QS_PATH, "r");
  ASSERT_NE(file, (void*)(NULL));
  ASSERT_EQ(mm_read_banner(file, &matcode), 0);
  EXPECT_TRUE(mm_is_array(matcode))   << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_real(matcode))    << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_general(matcode)) << mm_typecode_to_str(matcode);
  {
    isvd_int_t m_, Nl_;
    ASSERT_EQ(mm_read_mtx_array_size(file, &m_, &Nl_), 0);
    ASSERT_EQ(m_,  m);
    ASSERT_EQ(Nl_, Nl);
  }

  isvd_val_t *qst0 = isvd_dmalloc(m * Nl);
  isvd_int_t ldqst0 = Nl;
  for ( isvd_int_t ic = 0; ic < Nl; ++ic ) {
    for ( isvd_int_t ir = 0; ir < m; ++ir ) {
      EXPECT_EQ(fscanf(file, "%lg", &qst0[ir*ldqst0+ic]), 1);
    }
  }

  if ( file != stdin ) {
    fclose(file);
  }

  // Sets parameters
  const isvd_int_t n = m;
  const isvd_int_t k = 11;
  const isvd_int_t p = 0;
  const isvd_int_t l = k+p;
  const isvd_int_t N = Nl / l;
  ASSERT_EQ(Nl % l, 0);

  const isvd_Param param = isvd_createParam(m, n, k, p, N, mpi_root, MPI_COMM_WORLD);

  const isvd_int_t mb  = param.nrow_each;
  const isvd_int_t Pmb = param.nrow_total;

  // Creates matrices
  isvd_val_t *yst = yst0 + param.rowrange.begin * ldyst0;
  isvd_int_t ldyst = ldyst0;

  // Sketches
  isvd_dOrthogonalizeGramian(param, yst, ldyst);

  // Gather result
  isvd_val_t *qst_ = isvd_dmalloc(Pmb * Nl);
  isvd_int_t ldqst_ = Nl;
  MPI_Gather(yst, mb*ldyst, MPI_DOUBLE, qst_, mb*ldyst, MPI_DOUBLE, mpi_root, MPI_COMM_WORLD);

  // Compute space
  isvd_val_t *qqt_ = isvd_dmalloc(m * m);
  isvd_int_t ldqqt_ = m;
  isvd_val_t *qqt0 = isvd_dmalloc(m * m);
  isvd_int_t ldqqt0 = m;
  cblas_dsyrk(CblasColMajor, CblasUpper, CblasTrans, m, Nl, 1.0, qst_, ldqst_, 0.0, qqt_, ldqqt_);
  cblas_dsyrk(CblasColMajor, CblasUpper, CblasTrans, m, Nl, 1.0, qst0, ldqst0, 0.0, qqt0, ldqqt0);

  // Checks result
  if ( mpi_rank == mpi_root ) {
    for ( isvd_int_t ir = 0; ir < m; ++ir ) {
      for ( isvd_int_t ic = ir; ic < m; ++ic ) {
        ASSERT_NEAR(qqt_[ir+ic*ldqqt_], qqt0[ir+ic*ldqqt0], 1e-8) << "(ir, ic) =  (" << ir << ", " << ic << ")";
      }
    }
  }
}
