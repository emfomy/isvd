////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/def.h
/// @brief   The iSVD definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef ISVD_DEF_H_
#define ISVD_DEF_H_

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <complex.h>
#include <math.h>
#include <isvd/config.h>

#define ISVD_UNUSED( x ) (void)(x)

/// @ingroup  core_module
/// The type of index.
#ifndef ISVD_USE_ILP64
typedef int32_t index_t;
#else  // ISVD_USE_ILP64
typedef int64_t index_t;
#endif  // ISVD_USE_ILP64

#ifdef ISVD_USE_MKL
#define MKL_INT index_t
#define MKL_Complex8  float complex
#define MKL_Complex16 double complex
#endif  // ISVD_USE_MKL

/// @ingroup  core_module
//@{
#ifndef ISVD_USE_GTEST

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

#else  // ISVD_USE_GTEST

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

#endif  // ISVD_USE_GTEST

#define isvd_assert_pass( condition )  { bool err = condition; ISVD_UNUSED(err); isvd_assert_eq(err, 0); }
//@}

#endif  // ISVD_DEF_H_
