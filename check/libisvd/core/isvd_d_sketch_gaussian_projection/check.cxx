#include <gtest/gtest.h>
#include <mpi.h>
#include <mmio/mmio.h>
#include <isvd.h>

#define A_PATH  ISVD_DATA_PATH "/a.mtx"
#define YS_PATH ISVD_DATA_PATH "/ys_gp.mtx"

void test( char dista, char ordera ) {

  const mpi_int_t mpi_rank = isvd_getMpiRank(MPI_COMM_WORLD);
  const mpi_int_t mpi_root = 0;

        isvd_int_t m;
        isvd_int_t n;
  const isvd_int_t k  = 6;
  const isvd_int_t p  = 5;
  const isvd_int_t N  = 12;
  const isvd_int_t l  = k+p;
  const isvd_int_t Nl = N*l;

  FILE *file;
  MM_typecode matcode;

  // Check arguments
  char dista_  = isvd_arg2char("STOREA", dista,  "CR", "CR");
  char ordera_ = isvd_arg2char("ORDERA", ordera, "CR", "CR");
  ASSERT_NE(dista_,  '\0');
  ASSERT_NE(ordera_, '\0');

  // Reads A
  file = fopen(A_PATH, "r");
  ASSERT_NE(file, (void*)(NULL));
  ASSERT_EQ(mm_read_banner(file, &matcode), 0);
  EXPECT_TRUE(mm_is_array(matcode))   << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_real(matcode))    << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_general(matcode)) << mm_typecode_to_str(matcode);
  ASSERT_EQ(mm_read_mtx_array_size(file, &m, &n), 0);

  double *a0 = isvd_dmalloc(m * n);
  isvd_int_t lda0;
  if ( ordera_ == 'C' ) {
    lda0 = m;
    for ( isvd_int_t ic = 0; ic < n; ++ic ) {
      for ( isvd_int_t ir = 0; ir < m; ++ir ) {
        fscanf(file, "%lg", &a0[ir+ic*lda0]);
      }
    }
  } else {
    lda0 = n;
    for ( isvd_int_t ic = 0; ic < n; ++ic ) {
      for ( isvd_int_t ir = 0; ir < m; ++ir ) {
        fscanf(file, "%lg", &a0[ir*lda0+ic]);
      }
    }
  }

  if ( file != stdin ) {
    fclose(file);
  }

  // Reads data
  file = fopen(YS_PATH, "r");
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

  double *yst0 = isvd_dmalloc(m * Nl);
  isvd_int_t ldyst0 = Nl;

  for ( isvd_int_t ic = 0; ic < Nl; ++ic ) {
    for ( isvd_int_t ir = 0; ir < m; ++ir ) {
      fscanf(file, "%lg", &yst0[ir*ldyst0+ic]);
    }
  }

  if ( file != stdin ) {
    fclose(file);
  }

  // Sets parameters
  const isvd_Param param = isvd_createParam(m, n, k, p, N, mpi_root, MPI_COMM_WORLD);
  const isvd_int_t seed = 0;

  isvd_int_t mb  = param.nrow_each;
  isvd_int_t Pmb = param.nrow_total;

  // Creates matrices
  double *a;
  if ( dista_ == 'C' ) {
    if ( ordera_ == 'C' ) {
      a = a0 + param.colrange.begin * lda0;
    } else {
      a = a0 + param.colrange.begin;
    }
  } else {
    if ( ordera_ == 'C' ) {
      a = a0 + param.rowrange.begin;
    } else {
      a = a0 + param.rowrange.begin * lda0;
    }
  }
  isvd_int_t lda = lda0;

  double *yst = isvd_dmalloc(mb * Nl);
  isvd_int_t ldyst = Nl;

  // Sketches
  isvd_dSketchGaussianProjection(dista_, ordera_, param, a, lda, yst, ldyst, seed, mpi_root);

  // Gather result
  double *yst_ = isvd_dmalloc(Pmb * Nl);
  isvd_int_t ldyst_ = Nl;
  MPI_Gather(yst, mb*ldyst, MPI_DOUBLE, yst_, mb*ldyst, MPI_DOUBLE, mpi_root, MPI_COMM_WORLD);

  // Checks result
  if ( mpi_rank == mpi_root ) {
    for ( isvd_int_t ir = 0; ir < m; ++ir ) {
      for ( isvd_int_t ic = 0; ic < Nl; ++ic ) {
        ASSERT_NEAR(yst_[ir*ldyst_+ic], yst0[ir*ldyst0+ic], 1e-8) << "(ir, ic) =  (" << ir << ", " << ic << ")";
      }
    }
  }
}

TEST(SketchGaussianProjection, BlockCol_ColMajor) {
  test('C', 'C');
}

TEST(SketchGaussianProjection, BlockCol_RowMajor) {
  test('C', 'R');
}

TEST(SketchGaussianProjection, BlockRow_ColMajor) {
  test('R', 'C');
}

TEST(SketchGaussianProjection, BlockRow_RowMajor) {
  test('R', 'R');
}
