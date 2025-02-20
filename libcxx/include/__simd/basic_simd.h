//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___SIMD_BASIC_SIMD_H
#define _LIBCPP___SIMD_BASIC_SIMD_H

#include <__concepts/convertible_to.h>
#include <__config>
#include <__simd/abi.h>
#include <__simd/basic_simd_mask.h>

#if _LIBCPP_STD_VER >= 26

_LIBCPP_BEGIN_NAMESPACE_STD
namespace datapar {

template <class _Tp, class _Abi>
class basic_simd {
public:
  using value_type = _Tp;
  using mask_type  = basic_simd_mask<sizeof(_Tp), _Abi>;
  using abi_type   = _Abi;

private:
  abi_type::_SimdT __data_;

public:
  static constexpr integral_constant<__simd_size_type, __simd_size_v<value_type, abi_type>> size {};

  constexpr basic_simd() noexcept = default;

  template <convertible_to<value_type> _Up>

};

template <class _Tp, __simd_size_type _Np = __simd_size_v<_Tp, __native_abi<_Tp>>>
using simd = basic_simd<_Tp, __deduce_abi_t<_Tp, _Np>>;

} // namespace datapar
_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP_STD_VER >= 26

#endif // _LIBCPP___SIMD_BASIC_SIMD_H
