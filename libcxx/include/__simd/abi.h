//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___SIMD_BASIC_ABI_H
#define _LIBCPP___SIMD_BASIC_ABI_H

#include <__config>
#include <__type_traits/is_integral.h>
#include <__type_traits/is_signed.h>
#include <__type_traits/standard_types.h>
#include <limits>

#if _LIBCPP_STD_VER >= 26

_LIBCPP_BEGIN_NAMESPACE_STD
namespace datapar {

template <class _Tp>
inline constexpr bool __is_vectorizable_type_v = __is_standard_integer_type_v<_Tp> || __is_character_type_v<_Tp>;

template <>
inline constexpr bool __is_vectorizable_type_v<float> = true;

template <>
inline constexpr bool __is_vectorizable_type_v<double> = true;

template <class _Tp, class _Up>
inline constexpr bool __is_value_preverving = [] {
  if constexpr (is_integral_v<_Tp> && is_integral_v<_Up>)
    return is_signed_v<_Tp> == is_signed_v<_Up> && sizeof(_Tp) <= sizeof(_Up);
  else if constexpr (is_floating_point_v<_Tp> && is_floating_point_v<_Up>) {
    return numeric_limits<_Tp>::
  }
  else if constexpr (is_floating_point_v<_Tp>) {

  }
}();

// [simd.expos]
using __simd_size_type = int;

template <class _Tp>
struct __deduce_abi;

template <class _Tp, __simd_size_type _Np>
  requires __is_vectorizable_type_v<_Tp> && (_Np <= 64)
using __deduce_abi_t = __deduce_abi<_Tp>::template __apply<_Np>;

template <class _Tp>
using __native_abi = __deduce_abi<_Tp>::template __apply<1>;

template <class _Tp, class _Abi>
inline constexpr __simd_size_type __simd_size_v = 0;

// ABI Types

template <class _Tp, __simd_size_type _Np>
struct __vector_size_abi {
  using _SimdT [[__gnu__::__vector_size__(_Np * sizeof(_Tp))]] = _Tp;
  using _MaskT = _SimdT;
};

template <class _Tp>
  requires __is_vectorizable_type_v<_Tp>
struct __deduce_abi<_Tp> {
  template <__simd_size_type _Np>
  using __apply = __vector_size_abi<_Tp, _Np>;
};

template <class _Tp, __simd_size_type _Np>
inline constexpr __simd_size_type __simd_size_v<_Tp, __vector_size_abi<_Tp, _Np>> = _Np;

} // namespace datapar
_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP_STD_VER >= 26

#endif // _LIBCPP___SIMD_BASIC_ABI_H
