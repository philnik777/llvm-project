//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03, c++11, c++14, c++17, c++20, c++23

// template <class T, size_t N>
// class inplace_vector {
// public:
//   using value_type             = T;
//   using pointer                = T*;
//   using const_pointer          = const T*;
//   using reference              = value_type&;
//   using const_reference        = const value_type&;
//   using size_type              = size_t;
//   using difference_type        = ptrdiff_t;
//   using iterator               = implementation-defined;
//   using const_iterator         = implementation-defined;
//   using reverse_iterator       = std::reverse_iterator<iterator>;
//   using const_reverse_iterator = std::reverse_iterator<const_iterator>;
// };

#include <inplace_vector>
#include <type_traits>

template <class T>
constexpr bool test() {
  using InVec = std::inplace_vector<T, 1>;
  static_assert(std::is_same_v<typename InVec::value_type, T>);
  static_assert(std::is_same_v<typename InVec::pointer, T*>);
  static_assert(std::is_same_v<typename InVec::const_pointer, const T*>);
  static_assert(std::is_same_v<typename InVec::reference, T&>);
  static_assert(std::is_same_v<typename InVec::const_reference, const T&>);
  static_assert(std::is_same_v<typename InVec::size_type, size_t>);
  static_assert(std::is_same_v<typename InVec::difference_type, ptrdiff_t>);
  static_assert(std::is_same_v<typename InVec::reverse_iterator, std::reverse_iterator<typename InVec::iterator>>);
  static_assert(
      std::is_same_v<typename InVec::const_reverse_iterator, std::reverse_iterator<typename InVec::const_iterator>>);

  return true;
}

struct S {};

static_assert(test<S>());
static_assert(test<int>());
