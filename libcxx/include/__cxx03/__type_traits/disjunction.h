//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___CXX03___TYPE_TRAITS_DISJUNCTION_H
#define _LIBCPP___CXX03___TYPE_TRAITS_DISJUNCTION_H

#include <__cxx03/__config>
#include <__cxx03/__type_traits/integral_constant.h>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

template <bool>
struct _OrImpl;

template <>
struct _OrImpl<true> {
  template <class _Res, class _First, class... _Rest>
  using _Result _LIBCPP_NODEBUG =
      typename _OrImpl<!bool(_First::value) && sizeof...(_Rest) != 0>::template _Result<_First, _Rest...>;
};

template <>
struct _OrImpl<false> {
  template <class _Res, class...>
  using _Result = _Res;
};

// _Or always performs lazy evaluation of its arguments.
//
// However, `_Or<_Pred...>` itself will evaluate its result immediately (without having to
// be instantiated) since it is an alias, unlike `disjunction<_Pred...>`, which is a struct.
// If you want to defer the evaluation of `_Or<_Pred...>` itself, use `_Lazy<_Or, _Pred...>`
// or `disjunction<_Pred...>` directly.
template <class... _Args>
using _Or _LIBCPP_NODEBUG = typename _OrImpl<sizeof...(_Args) != 0>::template _Result<false_type, _Args...>;

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___CXX03___TYPE_TRAITS_DISJUNCTION_H
