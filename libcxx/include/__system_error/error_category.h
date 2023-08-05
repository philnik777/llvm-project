// -*- C++ -*-
//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___SYSTEM_ERROR_ERROR_CATEGORY_H
#define _LIBCPP___SYSTEM_ERROR_ERROR_CATEGORY_H

#include <__compare/ordering.h>
#include <__config>
#include <string>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

class _LIBCPP_EXPORTED_FROM_ABI error_condition;
class _LIBCPP_EXPORTED_FROM_ABI error_code;

class _LIBCPP_HIDDEN __do_message;

class _LIBCPP_EXPORTED_FROM_ABI error_category {
public:
  virtual ~error_category() noexcept;

#if defined(_LIBCPP_ERROR_CATEGORY_DEFINE_LEGACY_INLINE_FUNCTIONS)
  error_category() noexcept;
#else
  _LIBCPP_HIDE_FROM_ABI _LIBCPP_CONSTEXPR_SINCE_CXX14 error_category() noexcept = default;
#endif
  error_category(const error_category&)            = delete;
  error_category& operator=(const error_category&) = delete;

  virtual const char* name() const noexcept = 0;
  virtual error_condition default_error_condition(int __ev) const noexcept;
  virtual bool equivalent(int __code, const error_condition& __condition) const noexcept;
  virtual bool equivalent(const error_code& __code, int __condition) const noexcept;
  virtual string message(int __ev) const = 0;

  _LIBCPP_HIDE_FROM_ABI bool operator==(const error_category& __rhs) const noexcept { return this == &__rhs; }

#if _LIBCPP_STD_VER >= 20

  _LIBCPP_HIDE_FROM_ABI strong_ordering operator<=>(const error_category& __rhs) const noexcept {
    return compare_three_way()(this, std::addressof(__rhs));
  }

#else // _LIBCPP_STD_VER >= 20

  _LIBCPP_HIDE_FROM_ABI bool operator!=(const error_category& __rhs) const noexcept { return !(*this == __rhs); }

  _LIBCPP_HIDE_FROM_ABI bool operator<(const error_category& __rhs) const noexcept { return this < &__rhs; }

#endif // _LIBCPP_STD_VER >= 20

  friend class _LIBCPP_HIDDEN __do_message;
};

class _LIBCPP_HIDDEN __do_message : public error_category {
public:
  string message(int __ev) const override;
};

_LIBCPP_EXPORTED_FROM_ABI const error_category& generic_category() noexcept;
_LIBCPP_EXPORTED_FROM_ABI const error_category& system_category() noexcept;

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___SYSTEM_ERROR_ERROR_CATEGORY_H
