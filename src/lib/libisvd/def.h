////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file       lib/libisvd/def.h
/// \brief      The definitions.
///
/// \author     Mu Yang <<emfomy@gmail.com>>
/// \copyright  Copyright (c) 2017-2018 Mu Yang.
/// \license    This project is released under the \ref Readme_License "MIT License".
///

#ifndef LIBISVD_DEF_H_
#define LIBISVD_DEF_H_

#include <isvd/def.h>
#include <mpi.h>

#if defined(ISVD_USE_GTEST) && defined(__cplusplus)
  #include <gtest/gtest.h>
#endif  // ISVD_USE_GTEST

#define ISVD_UNUSED( x ) (void)(x)

#if !defined(__cplusplus) || (__cplusplus < 201103L)
  #define nullptr (void*)(NULL)
#endif

#if defined(__cplusplus)
extern "C" {
#endif  // __cplusplus

/// \ingroup  src_module
//\{
#if defined(ISVD_USE_GTEST) && defined(__cplusplus)

#define isvd_assert_true( condition )   EXPECT_TRUE(condition);
#define isvd_assert_false( condition )  EXPECT_FALSE(condition);

#define isvd_assert_eq( val1, val2 )  EXPECT_EQ(val1, val2);
#define isvd_assert_ne( val1, val2 )  EXPECT_NE(val1, val2);
#define isvd_assert_lt( val1, val2 )  EXPECT_LT(val1, val2);
#define isvd_assert_le( val1, val2 )  EXPECT_LE(val1, val2);
#define isvd_assert_gt( val1, val2 )  EXPECT_GT(val1, val2);
#define isvd_assert_ge( val1, val2 )  EXPECT_GE(val1, val2);

#define isvd_assert_gtlt( val, bound1, bound2 )  { EXPECT_GT(val, bound1); EXPECT_LT(val, bound2); }
#define isvd_assert_gtle( val, bound1, bound2 )  { EXPECT_GT(val, bound1); EXPECT_LE(val, bound2); }
#define isvd_assert_gelt( val, bound1, bound2 )  { EXPECT_GE(val, bound1); EXPECT_LT(val, bound2); }
#define isvd_assert_gele( val, bound1, bound2 )  { EXPECT_GE(val, bound1); EXPECT_LE(val, bound2); }

#else  // ISVD_USE_GTEST && __cplusplus

#define isvd_assert_true( condition )   assert(condition);
#define isvd_assert_false( condition )  assert(!(condition));

#define isvd_assert_eq( val1, val2 )  assert(val1 == val2);
#define isvd_assert_ne( val1, val2 )  assert(val1 != val2);
#define isvd_assert_lt( val1, val2 )  assert(val1 <  val2);
#define isvd_assert_le( val1, val2 )  assert(val1 <= val2);
#define isvd_assert_gt( val1, val2 )  assert(val1 >  val2);
#define isvd_assert_ge( val1, val2 )  assert(val1 >= val2);

#define isvd_assert_gtlt( val, bound1, bound2 )  assert(val >  bound1 && val <  bound2);
#define isvd_assert_gtle( val, bound1, bound2 )  assert(val >  bound1 && val <= bound2);
#define isvd_assert_gelt( val, bound1, bound2 )  assert(val >= bound1 && val <  bound2);
#define isvd_assert_gele( val, bound1, bound2 )  assert(val >= bound1 && val <= bound2);

#endif  // ISVD_USE_GTEST && __cplusplus

#define isvd_assert_pass( condition )  { isvd_assert_eq(condition, 0); }
#define isvd_assert_code( condition )  { isvd_assert_ne(condition, 0); }
#define isvd_assert_fail()  { isvd_assert_true(false); }
//\}

/// \ingroup  src_module
#define isvd_disp( format, expression ) printf(#expression " \t= " format "\n", expression);

/// \ingroup  src_module
#define isvd_vdisp( format, len, vector, inc ) printf(#vector ":\n"); \
  for ( isvd_int_t _isvd_i_ = 0; _isvd_i_ < len; ++_isvd_i_ ) { \
    printf(format "\t", (vector)[_isvd_i_ * inc]); \
  } \
  printf("\n");

/// \ingroup  src_module
#define isvd_mcdisp( format, nrow, ncol, matrix, ld ) printf(#matrix ":\n"); \
  for ( isvd_int_t _isvd_i_ = 0; _isvd_i_ < nrow; ++_isvd_i_ ) { \
    for ( isvd_int_t _isvd_j_ = 0; _isvd_j_ < ncol; ++_isvd_j_ ) { \
      printf(format "\t", (matrix)[_isvd_i_ + _isvd_j_ * ld]); \
    } \
    printf("\n"); \
  }

/// \ingroup  src_module
#define isvd_mrdisp( format, nrow, ncol, matrix, ld ) printf(#matrix ":\n"); \
  for ( isvd_int_t _isvd_i_ = 0; _isvd_i_ < nrow; ++_isvd_i_ ) { \
    for ( isvd_int_t _isvd_j_ = 0; _isvd_j_ < ncol; ++_isvd_j_ ) { \
      printf(format "\t", (matrix)[_isvd_i_ * ld + _isvd_j_]); \
    } \
    printf("\n"); \
  }

#if defined(__cplusplus)
}
#endif  // __cplusplus

#endif  // LIBISVD_DEF_H_
