//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef TEST_STD_NUMERICS_SIMD_UTILS_H
#define TEST_STD_NUMERICS_SIMD_UTILS_H

#include <type_traits>

#include "type_algorithms.h"

namespace types {
using vectorizable_types = types::standard_integer_types;
} // namespace types

namespace simd_utils {
template <class Func>
constexpr void test_sizes(Func f) {
  f(std::integral_constant<int, 1>{});
  f(std::integral_constant<int, 2>{});
  f(std::integral_constant<int, 3>{});
  f(std::integral_constant<int, 4>{});
  f(std::integral_constant<int, 8>{});
  f(std::integral_constant<int, 15>{});
  f(std::integral_constant<int, 16>{});
  f(std::integral_constant<int, 17>{});
  f(std::integral_constant<int, 32>{});
  f(std::integral_constant<int, 64>{});
}
} // namespace simd_utils

#endif // TEST_STD_NUMERICS_SIMD_UTILS_H
