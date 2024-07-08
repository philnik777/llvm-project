//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03, c++11, c++14, c++17, c++20, c++23

// constexpr inplace_vector() noexcept;

#include <cassert>
#include <inplace_vector>
#include <string>
#include <type_traits>

template <class T>
constexpr void test() {
  static_assert(std::is_nothrow_default_constructible_v<std::inplace_vector<T, 2>>);
  std::inplace_vector<T, 2> vec;
  assert(vec.size() == 0);
}

constexpr bool test() {
  test<int>();
  test<std::string>();

  return true;
}

int main() {
  test();
#if defined(__cpp_lib_constexpr_new) && __cpp_lib_constexpr_new >= 202400L
  static_assert(test());
#endif
}
