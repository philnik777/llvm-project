//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___SIMD_BASIC_SIMD_MASK_H
#define _LIBCPP___SIMD_BASIC_SIMD_MASK_H

#include <__config>
#include <__cstddef/size_t.h>
#include <__simd/abi.h>

#if _LIBCPP_STD_VER >= 26

_LIBCPP_BEGIN_NAMESPACE_STD
namespace datapar {

template <size_t _Bytes, class _Abi>
class basic_simd_mask;

template <class _Tp, __simd_size_type _Np = __simd_size_v<_Tp, __native_abi<_Tp>>>
using simd_mask = basic_simd_mask<sizeof(_Tp), __deduce_abi_t<_Tp, _Np>>;

} // namespace datapar
_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP_STD_VER >= 26

#endif // _LIBCPP___SIMD_BASIC_SIMD_MASK_H
