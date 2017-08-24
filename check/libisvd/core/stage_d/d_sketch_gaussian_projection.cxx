#include <gtest/gtest.h>
#include <mpi.h>
#include <mmio/mmio.h>
#include <isvd.h>

#define A_PATH  ISVD_DATA_PATH "/a.mtx"
#define YS_PATH ISVD_DATA_PATH "/ys_gp.mtx"

typedef double isvd_val_t;

static void test( char dista, char ordera ) {

  const mpi_int_t mpi_rank = isvd_getMpiRank(MPI_COMM_WORLD);
  const mpi_int_t mpi_root = 0;

  int m;
  int n;
  int Nl;

  FILE *file;
  MM_typecode matcode;

  // Check arguments
  const char dista_  = isvd_arg2char("DISTA",  dista,  "CR", NULL);
  const char ordera_ = isvd_arg2char("ORDERA", ordera, "CR", NULL);
  ASSERT_NE(dista_,  '\0');
  ASSERT_NE(ordera_, '\0');

  // Read A
  file = fopen(A_PATH, "r");
  ASSERT_NE(file, (void*)(NULL));
  ASSERT_EQ(mm_read_banner(file, &matcode), 0);
  EXPECT_TRUE(mm_is_array(matcode))   << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_real(matcode))    << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_general(matcode)) << mm_typecode_to_str(matcode);
  ASSERT_EQ(mm_read_mtx_array_size(file, &m, &n), 0);

  isvd_val_t *a0 = isvd_dmalloc(m * n);
  isvd_int_t lda0;
  if ( ordera_ == 'C' ) {
    lda0 = m;
    for ( isvd_int_t ic = 0; ic < n; ++ic ) {
      for ( isvd_int_t ir = 0; ir < m; ++ir ) {
        EXPECT_EQ(fscanf(file, "%lg", &a0[ir+ic*lda0]), 1);
      }
    }
  } else {
    lda0 = n;
    for ( isvd_int_t ic = 0; ic < n; ++ic ) {
      for ( isvd_int_t ir = 0; ir < m; ++ir ) {
        EXPECT_EQ(fscanf(file, "%lg", &a0[ir*lda0+ic]), 1);
      }
    }
  }

  if ( file != stdin ) {
    fclose(file);
  }

  // Read Ys
  file = fopen(YS_PATH, "r");
  ASSERT_NE(file, (void*)(NULL));
  ASSERT_EQ(mm_read_banner(file, &matcode), 0);
  EXPECT_TRUE(mm_is_array(matcode))   << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_real(matcode))    << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_general(matcode)) << mm_typecode_to_str(matcode);
  {
    int m_;
    ASSERT_EQ(mm_read_mtx_array_size(file, &m_, &Nl), 0);
    ASSERT_EQ(m_, m);
  }

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

  // Set parameters
  const isvd_int_t k = Nl;
  const isvd_int_t p = 0;
  const isvd_int_t N = 1;

  const isvd_Param param = isvd_createParam(m, n, k, p, N, mpi_root, MPI_COMM_WORLD);

  const isvd_int_t mb  = param.nrow_each;
  const isvd_int_t Pmb = param.nrow_total;
  const isvd_int_t seed = 0;

  // Create matrices
  isvd_val_t *a;
  if ( dista_ == 'C' ) {
    if ( ordera_ == 'C' ) {
      a = a0 + param.colidxbegin * lda0;
    } else {
      a = a0 + param.colidxbegin;
    }
  } else {
    if ( ordera_ == 'C' ) {
      a = a0 + param.rowidxbegin;
    } else {
      a = a0 + param.rowidxbegin * lda0;
    }
  }
  isvd_int_t lda = lda0;

  isvd_val_t *yst = isvd_dmalloc(mb * Nl);
  isvd_int_t ldyst = Nl;

  // Run stage
  isvd_dSketchGaussianProjection(param, NULL, 0, NULL, 0, dista_, ordera_, a, lda, yst, ldyst, seed, mpi_root);

#if defined(ISVD_USE_MKL)
  // Gather results
  isvd_val_t *yst_ = isvd_dmalloc(Pmb * Nl);
  isvd_int_t ldyst_ = Nl;
  MPI_Gather(yst, mb*ldyst, MPI_DOUBLE, yst_, mb*ldyst, MPI_DOUBLE, mpi_root, MPI_COMM_WORLD);

  // Check results
  if ( mpi_rank == mpi_root ) {
    for ( isvd_int_t ir = 0; ir < m; ++ir ) {
      for ( isvd_int_t ic = 0; ic < Nl; ++ic ) {
        ASSERT_NEAR(yst_[ir*ldyst_+ic], yst0[ir*ldyst0+ic], 1e-8) << "(ir, ic) =  (" << ir << ", " << ic << ")";
      }
    }
  }
#else
  ISVD_UNUSED(mpi_rank);
  ISVD_UNUSED(Pmb);
#endif /// ISVD_USE_MKL
}

TEST(GaussianProjectionSketching, BlockCol_ColMajor) {
  test('C', 'C');
}

TEST(GaussianProjectionSketching, BlockCol_RowMajor) {
  test('C', 'R');
}

TEST(GaussianProjectionSketching, BlockRow_ColMajor) {
  test('R', 'C');
}

TEST(GaussianProjectionSketching, BlockRow_RowMajor) {
  test('R', 'R');
}
