//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___EXCEPTION_OPERATIONS_H
#define _LIBCPP___EXCEPTION_OPERATIONS_H

#include <__availability>
#include <__config>
#include <cstddef>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

namespace std { // purposefully not using versioning namespace
#if _LIBCPP_STD_VER <= 14 || defined(_LIBCPP_ENABLE_CXX17_REMOVED_UNEXPECTED_FUNCTIONS) ||                             \
    defined(_LIBCPP_BUILDING_LIBRARY)
using unexpected_handler = void (*)();
_LIBCPP_EXPORTED_FROM_ABI unexpected_handler set_unexpected(unexpected_handler) noexcept;
_LIBCPP_EXPORTED_FROM_ABI unexpected_handler get_unexpected() noexcept;
[[noreturn]] _LIBCPP_EXPORTED_FROM_ABI void unexpected();
#endif

using terminate_handler = void (*)();
_LIBCPP_EXPORTED_FROM_ABI terminate_handler set_terminate(terminate_handler) noexcept;
_LIBCPP_EXPORTED_FROM_ABI terminate_handler get_terminate() noexcept;

_LIBCPP_EXPORTED_FROM_ABI bool uncaught_exception() noexcept;
_LIBCPP_EXPORTED_FROM_ABI _LIBCPP_AVAILABILITY_UNCAUGHT_EXCEPTIONS int uncaught_exceptions() noexcept;

class _LIBCPP_EXPORTED_FROM_ABI exception_ptr;

_LIBCPP_EXPORTED_FROM_ABI exception_ptr current_exception() noexcept;
[[noreturn]] _LIBCPP_EXPORTED_FROM_ABI void rethrow_exception(exception_ptr);
} // namespace std

#endif // _LIBCPP___EXCEPTION_OPERATIONS_H
