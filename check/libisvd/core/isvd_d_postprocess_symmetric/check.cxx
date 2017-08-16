#include <gtest/gtest.h>
#include <mpi.h>
#include <mmio/mmio.h>
#include <isvd.h>

#define A_PATH ISVD_DATA_PATH "/a_sym.mtx"
#define Q_PATH ISVD_DATA_PATH "/q.mtx"
#define S_PATH ISVD_DATA_PATH "/s_sym.mtx"
#define U_PATH ISVD_DATA_PATH "/u_sym.mtx"

typedef double isvd_val_t;

typedef enum {
  GatherUV,
  BlockUV,
  NoUV
} JobUV;

static void test( char dista, char ordera, const JobUV jobuv ) {

  const mpi_int_t mpi_rank = isvd_getMpiRank(MPI_COMM_WORLD);
  const mpi_int_t mpi_root = 0;

  isvd_int_t m;
  isvd_int_t n;
  isvd_int_t l;

  FILE *file;
  MM_typecode matcode;

  // Check arguments
  const char dista_  = isvd_arg2char("DISTA",  dista,  "CR");
  const char ordera_ = isvd_arg2char("ORDERA", ordera, "CR");
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

  // Read Q
  file = fopen(Q_PATH, "r");
  ASSERT_NE(file, (void*)(NULL));
  ASSERT_EQ(mm_read_banner(file, &matcode), 0);
  EXPECT_TRUE(mm_is_array(matcode))   << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_real(matcode))    << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_general(matcode)) << mm_typecode_to_str(matcode);
  {
    isvd_int_t m_;
    ASSERT_EQ(mm_read_mtx_array_size(file, &m_, &l), 0);
    ASSERT_EQ(m_, m);
  }

  isvd_val_t *qt0 = isvd_dmalloc(m * l);
  isvd_int_t ldqt0 = l;
  for ( isvd_int_t ic = 0; ic < l; ++ic ) {
    for ( isvd_int_t ir = 0; ir < m; ++ir ) {
      EXPECT_EQ(fscanf(file, "%lg", &qt0[ir*ldqt0+ic]), 1);
    }
  }

  if ( file != stdin ) {
    fclose(file);
  }

  // Read S
  file = fopen(S_PATH, "r");
  ASSERT_NE(file, (void*)(NULL));
  ASSERT_EQ(mm_read_banner(file, &matcode), 0);
  EXPECT_TRUE(mm_is_array(matcode))   << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_real(matcode))    << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_general(matcode)) << mm_typecode_to_str(matcode);
  {
    isvd_int_t l_, one_;
    ASSERT_EQ(mm_read_mtx_array_size(file, &l_, &one_), 0);
    ASSERT_EQ(l_,   l);
    ASSERT_EQ(one_, 1);
  }

  isvd_val_t *s0 = isvd_dmalloc(l);
  for ( isvd_int_t ir = 0; ir < l; ++ir ) {
    EXPECT_EQ(fscanf(file, "%lg", &s0[ir]), 1);
  }

  if ( file != stdin ) {
    fclose(file);
  }

  // Read U
  file = fopen(U_PATH, "r");
  ASSERT_NE(file, (void*)(NULL));
  ASSERT_EQ(mm_read_banner(file, &matcode), 0);
  EXPECT_TRUE(mm_is_array(matcode))   << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_real(matcode))    << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_general(matcode)) << mm_typecode_to_str(matcode);
  {
    isvd_int_t m_, l_;
    ASSERT_EQ(mm_read_mtx_array_size(file, &m_, &l_), 0);
    ASSERT_EQ(m_, m);
    ASSERT_EQ(l_, l);
  }

  isvd_val_t *ut0 = isvd_dmalloc(m * l);
  isvd_int_t ldut0 = l;
  for ( isvd_int_t ic = 0; ic < l; ++ic ) {
    for ( isvd_int_t ir = 0; ir < m; ++ir ) {
      EXPECT_EQ(fscanf(file, "%lg", &ut0[ir*ldqt0+ic]), 1);
    }
  }

  if ( file != stdin ) {
    fclose(file);
  }

  // Set parameters
  ASSERT_EQ(m, n);

  const isvd_int_t k = l;
  const isvd_int_t p = 0;
  const isvd_int_t N = 1;

  const isvd_Param param = isvd_createParam(m, n, k, p, N, mpi_root, MPI_COMM_WORLD);

  const isvd_int_t mb  = param.nrow_each;
  const isvd_int_t Pmb = param.nrow_total;

  // Create matrices
  isvd_val_t *a;
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

  isvd_val_t *qt = qt0 + param.rowrange.begin * ldqt0;
  isvd_int_t ldqt = ldqt0;

  isvd_val_t *s = isvd_dmalloc(l);

  isvd_val_t *ut_ = isvd_dmalloc(Pmb * l);
  isvd_int_t ldut_ = l;

  switch ( jobuv ) {
    case GatherUV: {

      // Run stage
      isvd_dPostprocessSymmetric(param, NULL, 0, NULL, 0, dista_, ordera_, a, lda, qt, ldqt, s, ut_, ldut_, mpi_root);

      break;
    }

    case BlockUV: {

      // Create matrices
      isvd_val_t *ut = isvd_dmalloc(mb * l);
      isvd_int_t ldut = l;

      // Run stage
      isvd_dPostprocessSymmetric(param, NULL, 0, NULL, 0, dista_, ordera_, a, lda, qt, ldqt, s, ut, ldut, -1);

      // Gather results
      MPI_Gather(ut, mb*ldut, MPI_DOUBLE, ut_, mb*ldut, MPI_DOUBLE, mpi_root, MPI_COMM_WORLD);

      break;
    }

    default: {

      // Run stage
      isvd_dPostprocessSymmetric(param, NULL, 0, NULL, 0, dista_, ordera_, a, lda, qt, ldqt, s, NULL, 0, -2);

      break;
    }
  }

  if ( jobuv != NoUV ) {
    // Compute space
    isvd_val_t *uut_ = isvd_dmalloc(m * m);
    isvd_int_t lduut_ = m;
    isvd_val_t *uut0 = isvd_dmalloc(m * m);
    isvd_int_t lduut0 = m;
    cblas_dsyrk(CblasColMajor, CblasUpper, CblasTrans, m, k, 1.0, ut_, ldut_, 0.0, uut_, lduut_);
    cblas_dsyrk(CblasColMajor, CblasUpper, CblasTrans, m, k, 1.0, ut0, ldut0, 0.0, uut0, lduut0);

    // Check results
    if ( mpi_rank == mpi_root ) {
      for ( isvd_int_t ir = 0; ir < l; ++ir ) {
        ASSERT_NEAR(s[ir], s0[ir], 1e-8) << "(ir, ic) =  (" << ir << ", " << 1 << ")";
      }
      for ( isvd_int_t ir = 0; ir < m; ++ir ) {
        for ( isvd_int_t ic = ir; ic < m; ++ic ) {
          ASSERT_NEAR(uut_[ir+ic*lduut_], uut0[ir+ic*lduut0], 1e-8) << "(ir, ic) =  (" << ir << ", " << ic << ")";
        }
      }
    }
  } else {
    if ( mpi_rank == mpi_root ) {
      for ( isvd_int_t ir = 0; ir < l; ++ir ) {
        ASSERT_NEAR(s[ir], s0[ir], 1e-8) << "(ir, ic) =  (" << ir << ", " << 1 << ")";
      }
    }
  }
}

TEST(SymmetricPostprocessing, BlockCol_ColMajor_GatherUV) {
  test('C', 'C', GatherUV);
}

TEST(SymmetricPostprocessing, BlockCol_RowMajor_GatherUV) {
  test('C', 'R', GatherUV);
}

TEST(SymmetricPostprocessing, BlockRow_ColMajor_GatherUV) {
  test('R', 'C', GatherUV);
}

TEST(SymmetricPostprocessing, BlockRow_RowMajor_GatherUV) {
  test('R', 'R', GatherUV);
}

TEST(SymmetricPostprocessing, BlockCol_ColMajor_BlockUV) {
  test('C', 'C', BlockUV);
}

TEST(SymmetricPostprocessing, BlockCol_RowMajor_BlockUV) {
  test('C', 'R', BlockUV);
}

TEST(SymmetricPostprocessing, BlockRow_ColMajor_BlockUV) {
  test('R', 'C', BlockUV);
}

TEST(SymmetricPostprocessing, BlockRow_RowMajor_BlockUV) {
  test('R', 'R', BlockUV);
}


TEST(SymmetricPostprocessing, BlockCol_ColMajor_NoUV) {
  test('C', 'C', NoUV);
}

TEST(SymmetricPostprocessing, BlockCol_RowMajor_NoUV) {
  test('C', 'R', NoUV);
}

TEST(SymmetricPostprocessing, BlockRow_ColMajor_NoUV) {
  test('R', 'C', NoUV);
}

TEST(SymmetricPostprocessing, BlockRow_RowMajor_NoUV) {
  test('R', 'R', NoUV);
}
