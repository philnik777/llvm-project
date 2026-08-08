//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___NEW_NEW_AT_LEAST_H
#define _LIBCPP___NEW_NEW_AT_LEAST_H

#include <__config>
#include <__cstddef/size_t.h>
#include <__new/align_val_t.h>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

template <class _Pointer, class _SizeT = size_t>
struct __allocation_result {
  _Pointer ptr;
  _SizeT count;

  _LIBCPP_HIDE_FROM_ABI _LIBCPP_CONSTEXPR __allocation_result(_Pointer __ptr, _SizeT __count)
      : ptr(__ptr), count(__count) {}
};
_LIBCPP_CTAD_SUPPORTED_FOR_TYPE(__allocation_result);

#if _LIBCPP_AVAILABILITY_HAS_NEW_AT_LEAST
_LIBCPP_BEGIN_EXPLICIT_ABI_ANNOTATIONS

_LIBCPP_MALLOC_SPAN _LIBCPP_EXPORTED_FROM_ABI __allocation_result<void*> __new_at_least(size_t);
#  if _LIBCPP_HAS_LIBRARY_ALIGNED_ALLOCATION
_LIBCPP_MALLOC_SPAN _LIBCPP_EXPORTED_FROM_ABI __allocation_result<void*> __new_at_least(size_t, align_val_t);
#  endif

_LIBCPP_END_EXPLICIT_ABI_ANNOTATIONS
#endif

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___NEW_NEW_AT_LEAST_H
