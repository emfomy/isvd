#include <gtest/gtest.h>
#include <mpi.h>
#include <mmio/mmio.h>
#include <isvd.h>

#define A_PATH ISVD_DATA_PATH "/a.mtx"
#define Q_PATH ISVD_DATA_PATH "/q.mtx"
#define S_PATH ISVD_DATA_PATH "/s.mtx"
#define U_PATH ISVD_DATA_PATH "/u.mtx"
#define V_PATH ISVD_DATA_PATH "/v.mtx"

typedef double isvd_val_t;

void testWithUV( char dista, char ordera ) {

  const mpi_int_t mpi_rank = isvd_getMpiRank(MPI_COMM_WORLD);
  const mpi_int_t mpi_root = 0;

  isvd_int_t m;
  isvd_int_t n;
  isvd_int_t l;

  FILE *file;
  MM_typecode matcode;

  // Check arguments
  char dista_  = isvd_arg2char("DISTA",  dista,  "CR", "CR");
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

  isvd_val_t *a0 = isvd_dmalloc(m * n);
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

  // Reads Q
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
      fscanf(file, "%lg", &qt0[ir*ldqt0+ic]);
    }
  }

  if ( file != stdin ) {
    fclose(file);
  }

  // Reads S
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
    fscanf(file, "%lg", &s0[ir]);
  }

  if ( file != stdin ) {
    fclose(file);
  }

  // Reads U
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
      fscanf(file, "%lg", &ut0[ir*ldqt0+ic]);
    }
  }

  if ( file != stdin ) {
    fclose(file);
  }

  // Reads V
  file = fopen(V_PATH, "r");
  ASSERT_NE(file, (void*)(NULL));
  ASSERT_EQ(mm_read_banner(file, &matcode), 0);
  EXPECT_TRUE(mm_is_array(matcode))   << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_real(matcode))    << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_general(matcode)) << mm_typecode_to_str(matcode);
  {
    isvd_int_t n_, l_;
    ASSERT_EQ(mm_read_mtx_array_size(file, &n_, &l_), 0);
    ASSERT_EQ(n_, n);
    ASSERT_EQ(l_, l);
  }

  isvd_val_t *vt0 = isvd_dmalloc(n * l);
  isvd_int_t ldvt0 = l;
  for ( isvd_int_t ic = 0; ic < l; ++ic ) {
    for ( isvd_int_t ir = 0; ir < n; ++ir ) {
      fscanf(file, "%lg", &vt0[ir*ldqt0+ic]);
    }
  }

  if ( file != stdin ) {
    fclose(file);
  }

  // Sets parameters
  const isvd_int_t k = l;
  const isvd_int_t p = 0;
  const isvd_int_t N = 1;

  const isvd_Param param = isvd_createParam(m, n, k, p, N, mpi_root, MPI_COMM_WORLD);

  const isvd_int_t Pmb = param.nrow_total;
  const isvd_int_t Pnb = param.ncol_total;

  // Creates matrices
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

  isvd_val_t *ut = isvd_dmalloc(Pmb * l);
  isvd_int_t ldut = l;

  isvd_val_t *vt = isvd_dmalloc(Pnb * l);
  isvd_int_t ldvt = l;

  // Sketches
  isvd_dPostprocessGramian('S', 'S', dista_, ordera_, param, a, lda, qt, ldqt, s, ut, ldut, vt, ldvt, mpi_root);

  // Checks result
  if ( mpi_rank == mpi_root ) {
    for ( isvd_int_t ir = 0; ir < l; ++ir ) {
      ASSERT_NEAR(s[ir], s0[ir], 1e-8) << "(ir, ic) =  (" << ir << ", " << 1 << ")";
    }
    for ( isvd_int_t ir = 0; ir < m; ++ir ) {
      for ( isvd_int_t ic = 0; ic < l; ++ic ) {
        ASSERT_NEAR(ut[ir*ldut+ic], ut0[ir*ldut0+ic], 1e-8) << "(ir, ic) =  (" << ir << ", " << ic << ")";
      }
    }
    for ( isvd_int_t ir = 0; ir < n; ++ir ) {
      for ( isvd_int_t ic = 0; ic < l; ++ic ) {
        ASSERT_NEAR(vt[ir*ldvt+ic], vt0[ir*ldvt0+ic], 1e-8) << "(ir, ic) =  (" << ir << ", " << ic << ")";
      }
    }
  }
}

TEST(PostprocessGramian, BlockCol_ColMajor_WithUV) {
  testWithUV('C', 'C');
}

// TEST(PostprocessGramian, BlockCol_RowMajor_WithUV) {
//   testWithUV('C', 'R');
// }

// TEST(PostprocessGramian, BlockRow_ColMajor_WithUV) {
//   testWithUV('R', 'C');
// }

// TEST(PostprocessGramian, BlockRow_RowMajor_WithUV) {
//   testWithUV('R', 'R');
// }

// TEST(PostprocessGramian, BlockCol_ColMajor_NoUV) {
//   testNoUV('C', 'C');
// }

// TEST(PostprocessGramian, BlockCol_RowMajor_NoUV) {
//   testNoUV('C', 'R');
// }

// TEST(PostprocessGramian, BlockRow_ColMajor_NoUV) {
//   testNoUV('R', 'C');
// }

// TEST(PostprocessGramian, BlockRow_RowMajor_NoUV) {
//   testNoUV('R', 'R');
// }
