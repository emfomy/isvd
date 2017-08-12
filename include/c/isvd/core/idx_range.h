////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/c/isvd/core/idx_range.h
/// @brief   The index range structure.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef _ISVD_CORE_IDX_RANGE_H_
#define _ISVD_CORE_IDX_RANGE_H_

#include <isvd/core/def.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  c_core_module
/// The index range.
///
typedef struct {

  /// The beginning index.
  isvd_int_t begin;

  /// The end index.
  isvd_int_t end;

} isvd_IdxRange;

#endif  // _ISVD_CORE_IDX_RANGE_H_
