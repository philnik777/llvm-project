//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___SIMD_ABI_H
#define _LIBCPP___SIMD_ABI_H

#include <__concepts/convertible_to.h>
#include <__concepts/equality_comparable.h>
#include <__config>
#include <__type_traits/standard_types.h>

#if _LIBCPP_STD_VER >= 26

_LIBCPP_BEGIN_NAMESPACE_STD
namespace datapar {

template <class _Tp>
inline constexpr bool __is_vectorizable_type_v = __is_standard_integer_type_v<_Tp> || __is_character_type_v<_Tp>;

template <>
inline constexpr bool __is_vectorizable_type_v<float> = true;

template <>
inline constexpr bool __is_vectorizable_type_v<double> = true;

template <class _From, class _To>
concept __value_preserving_convertible = requires(_From __from) { _To{__from}; };

template <class _Tp>
concept __constexpr_wrapper_like =
    convertible_to<_Tp, decltype(_Tp::value)> && equality_comparable_with<_Tp, decltype(_Tp::value)> &&
    bool_constant<_Tp() == _Tp::value>::value &&
    bool_constant<static_cast<decltype(_Tp::value)>(_Tp()) == _Tp::value>::value;

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

#endif // _LIBCPP___SIMD_ABI_H
