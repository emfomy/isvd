#include <gtest/gtest.h>
#include <mpi.h>
#include <mmio.h>
#include <isvd.h>
#include <libisvd.h>

#define A_PATH ISVD_DATA_PATH "/a_sym.mtx"
#define Q_PATH ISVD_DATA_PATH "/q.mtx"
#define S_PATH ISVD_DATA_PATH "/s_sym.mtx"
#define U_PATH ISVD_DATA_PATH "/u_sym.mtx"

#define serr 1e-3
#define derr 1e-8

typedef @xtype_____@ isvd_val_t;

typedef enum {
  GatherUV,
  BlockUV,
  NoUV
} JobUV;

static void test( char dista, char ordera, const JobUV jobuv ) {

  const mpi_int_t mpi_rank = isvd_getMpiRank(MPI_COMM_WORLD);
  const mpi_int_t mpi_root = 0;

  int m;
  int n;
  int l;

  FILE *file;
  MM_typecode matcode;

  // Check arguments
  const char dista_  = isvd_arg2char("DISTA",  dista,  "CR", NULL);
  const char ordera_ = isvd_arg2char("ORDERA", ordera, "CR", NULL);
  ASSERT_NE(dista_,  '\0');
  ASSERT_NE(ordera_, '\0');

  // Read A
  file = fopen(A_PATH, "r");
  ASSERT_NE(file, nullptr);
  ASSERT_EQ(mm_read_banner(file, &matcode), 0);
  EXPECT_TRUE(mm_is_array(matcode))   << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_real(matcode))    << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_general(matcode)) << mm_typecode_to_str(matcode);
  ASSERT_EQ(mm_read_mtx_array_size(file, &m, &n), 0);

  isvd_val_t *a0 = isvd_@x@malloc(m * n);
  isvd_int_t lda0;
  if ( ordera_ == 'C' ) {
    lda0 = m;
    for ( isvd_int_t ic = 0; ic < n; ++ic ) {
      for ( isvd_int_t ir = 0; ir < m; ++ir ) {
        isvd_@x@fget(file, &a0[ir+ic*lda0]);
      }
    }
  } else {
    lda0 = n;
    for ( isvd_int_t ic = 0; ic < n; ++ic ) {
      for ( isvd_int_t ir = 0; ir < m; ++ir ) {
        isvd_@x@fget(file, &a0[ir*lda0+ic]);
      }
    }
  }

  if ( file != stdin ) {
    fclose(file);
  }

  // Read Q
  file = fopen(Q_PATH, "r");
  ASSERT_NE(file, nullptr);
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

  // Read S
  file = fopen(S_PATH, "r");
  ASSERT_NE(file, nullptr);
  ASSERT_EQ(mm_read_banner(file, &matcode), 0);
  EXPECT_TRUE(mm_is_array(matcode))   << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_real(matcode))    << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_general(matcode)) << mm_typecode_to_str(matcode);
  {
    int l_, one_;
    ASSERT_EQ(mm_read_mtx_array_size(file, &l_, &one_), 0);
    ASSERT_EQ(l_,   l);
    ASSERT_EQ(one_, 1);
  }

  isvd_val_t *s0 = isvd_@x@malloc(l);
  for ( isvd_int_t ir = 0; ir < l; ++ir ) {
    isvd_@x@fget(file, &s0[ir]);
  }

  if ( file != stdin ) {
    fclose(file);
  }

  // Read U
  file = fopen(U_PATH, "r");
  ASSERT_NE(file, nullptr);
  ASSERT_EQ(mm_read_banner(file, &matcode), 0);
  EXPECT_TRUE(mm_is_array(matcode))   << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_real(matcode))    << mm_typecode_to_str(matcode);
  EXPECT_TRUE(mm_is_general(matcode)) << mm_typecode_to_str(matcode);
  {
    int m_, l_;
    ASSERT_EQ(mm_read_mtx_array_size(file, &m_, &l_), 0);
    ASSERT_EQ(m_, m);
    ASSERT_EQ(l_, l);
  }

  isvd_val_t *ut0 = isvd_@x@malloc(m * l);
  isvd_int_t ldut0 = l;
  for ( isvd_int_t ic = 0; ic < l; ++ic ) {
    for ( isvd_int_t ir = 0; ir < m; ++ir ) {
      isvd_@x@fget(file, &ut0[ir*ldqt0+ic]);
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

  const isvd_int_t mj  = param.nrow_proc;
  const isvd_int_t mb  = param.nrow_each;
  const isvd_int_t Pmb = param.nrow_total;
  const isvd_int_t nb  = param.ncol_each;
  const isvd_int_t Pnb = param.ncol_total;

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

  isvd_val_t *qt = isvd_@x@malloc(l * mb);
  isvd_int_t ldqt = l;
  isvd_@x@Omatcopy('N', l, mj, 1.0, qt0 + param.rowidxbegin * ldqt0, ldqt0, qt, ldqt);

  isvd_val_t *s = isvd_@x@malloc(l);

  isvd_val_t *ut_ = isvd_@x@malloc(l * Pmb);
  isvd_int_t ldut_ = l;

  isvd_val_t *vt_ = isvd_@x@malloc(l * Pnb);
  isvd_int_t ldvt_ = l;

  switch ( jobuv ) {
    case GatherUV: {

      // Run stage
      isvd_@x@PostprocessSymmetric(param, NULL, 0, NULL, 0, dista_, ordera_,
                                   a, lda, qt, ldqt, s, ut_, ldut_, vt_, ldvt_, mpi_root, mpi_root);

      break;
    }

    case BlockUV: {

      // Create matrices
      isvd_val_t *ut = isvd_@x@malloc(l * mb);
      isvd_int_t ldut = l;

      isvd_val_t *vt = isvd_@x@malloc(l * nb);
      isvd_int_t ldvt = l;

      // Run stage
      isvd_@x@PostprocessSymmetric(param, NULL, 0, NULL, 0, dista_, ordera_,
                                   a, lda, qt, ldqt, s, ut, ldut, vt, ldvt, -1, -1);

      // Gather results
      MPI_Gather(ut, mb*ldut, MPI_@XTYPE@, ut_, mb*ldut, MPI_@XTYPE@, mpi_root, MPI_COMM_WORLD);
      MPI_Gather(vt, nb*ldvt, MPI_@XTYPE@, vt_, nb*ldvt, MPI_@XTYPE@, mpi_root, MPI_COMM_WORLD);

      // Deallocate memory
      isvd_free(ut);
      isvd_free(vt);

      break;
    }

    case NoUV: {

      // Run stage
      isvd_@x@PostprocessSymmetric(param, NULL, 0, NULL, 0, dista_, ordera_,
                                   a, lda, qt, ldqt, s, NULL, 0, NULL, 0, -2, -2);

      break;
    }

    default: {
      FAIL() << "Unexpected default case!";
    }
  }

  // Check results
  if ( mpi_rank == mpi_root ) {
    for ( isvd_int_t ir = 0; ir < l; ++ir ) {
      ASSERT_NEAR(s[ir], s0[ir], @x@err) << "(ir, ic) =  (" << ir << ", " << 1 << ")";
    }
    if ( jobuv != NoUV ) {
      // Compute space
      isvd_val_t *uut_ = isvd_@x@malloc(m * m);
      isvd_int_t lduut_ = m;
      isvd_val_t *uut0 = isvd_@x@malloc(m * m);
      isvd_int_t lduut0 = m;
      isvd_val_t *vvt_ = isvd_@x@malloc(n * n);
      isvd_int_t ldvvt_ = n;
      isvd_val_t *vvt0 = uut0;
      isvd_int_t ldvvt0 = lduut0;
      isvd_@x@Syrk('U', 'T', m, k, 1.0, ut_, ldut_, 0.0, uut_, lduut_);
      isvd_@x@Syrk('U', 'T', m, k, 1.0, ut0, ldut0, 0.0, uut0, lduut0);
      isvd_@x@Syrk('U', 'T', n, k, 1.0, vt_, ldvt_, 0.0, vvt_, ldvvt_);

      // Check results
      for ( isvd_int_t ir = 0; ir < m; ++ir ) {
        for ( isvd_int_t ic = ir; ic < m; ++ic ) {
          ASSERT_NEAR(uut_[ir+ic*lduut_], uut0[ir+ic*lduut0], @x@err) << "(ir, ic) =  (" << ir << ", " << ic << ")";
        }
      }
      for ( isvd_int_t ir = 0; ir < n; ++ir ) {
        for ( isvd_int_t ic = ir; ic < n; ++ic ) {
          ASSERT_NEAR(vvt_[ir+ic*ldvvt_], vvt0[ir+ic*ldvvt0], @x@err) << "(ir, ic) =  (" << ir << ", " << ic << ")";
        }
      }

      // Deallocate memory
      isvd_free(uut_);
      isvd_free(uut0);
      isvd_free(vvt_);
    }
  }

  // Deallocate memory
  isvd_free(a0);
  isvd_free(qt0);
  isvd_free(s0);
  isvd_free(ut0);
  isvd_free(qt);
  isvd_free(s);
  isvd_free(ut_);
  isvd_free(vt_);
}

TEST(@XStr@_SymmetricPostprocessing, BlockCol_ColMajor_GatherUV) {
  test('C', 'C', GatherUV);
}

TEST(@XStr@_SymmetricPostprocessing, BlockCol_RowMajor_GatherUV) {
  test('C', 'R', GatherUV);
}

TEST(@XStr@_SymmetricPostprocessing, BlockRow_ColMajor_GatherUV) {
  test('R', 'C', GatherUV);
}

TEST(@XStr@_SymmetricPostprocessing, BlockRow_RowMajor_GatherUV) {
  test('R', 'R', GatherUV);
}

TEST(@XStr@_SymmetricPostprocessing, BlockCol_ColMajor_BlockUV) {
  test('C', 'C', BlockUV);
}

TEST(@XStr@_SymmetricPostprocessing, BlockCol_RowMajor_BlockUV) {
  test('C', 'R', BlockUV);
}

TEST(@XStr@_SymmetricPostprocessing, BlockRow_ColMajor_BlockUV) {
  test('R', 'C', BlockUV);
}

TEST(@XStr@_SymmetricPostprocessing, BlockRow_RowMajor_BlockUV) {
  test('R', 'R', BlockUV);
}


TEST(@XStr@_SymmetricPostprocessing, BlockCol_ColMajor_NoUV) {
  test('C', 'C', NoUV);
}

TEST(@XStr@_SymmetricPostprocessing, BlockCol_RowMajor_NoUV) {
  test('C', 'R', NoUV);
}

TEST(@XStr@_SymmetricPostprocessing, BlockRow_ColMajor_NoUV) {
  test('R', 'C', NoUV);
}

TEST(@XStr@_SymmetricPostprocessing, BlockRow_RowMajor_NoUV) {
  test('R', 'R', NoUV);
}
