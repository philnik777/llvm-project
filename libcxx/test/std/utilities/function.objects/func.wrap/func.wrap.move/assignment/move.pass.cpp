//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03, c++11, c++14, c++17, c++20

#include <cassert>
#include <functional>

#include "test_macros.h"
#include "../common.h"

template <class T>
void test() {
  static_assert(!std::is_assignable_v<std::move_only_function<T>, int>);
  {
    std::move_only_function<T> f = &call_func;
    std::move_only_function<T> f2;
    f2 = std::move(f);
    assert(f2);
    LIBCPP_ASSERT(!f);
  }
  {
    decltype(&call_func) ptr     = nullptr;
    std::move_only_function<T> f = ptr;
    std::move_only_function<T> f2;
    f2 = std::move(f);
    assert(!f2);
    LIBCPP_ASSERT(!f);
  }
  {
    std::move_only_function<T> f = TriviallyDestructible{};
    std::move_only_function<T> f2;
    f2 = std::move(f);
    assert(f2);
    LIBCPP_ASSERT(!f);
  }
  {
    std::move_only_function<T> f = TriviallyDestructibleTooLarge{};
    std::move_only_function<T> f2;
    f2 = std::move(f);
    assert(f2);
    LIBCPP_ASSERT(!f);
  }
  {
    std::move_only_function<T> f = NonTrivial{};
    std::move_only_function<T> f2;
    f2 = std::move(f);
    assert(f2);
    LIBCPP_ASSERT(!f);
  }
}

struct S {
  void func() noexcept {}
};

template <class T>
void test_member_function_pointer() {
  {
    std::move_only_function<T> f = &S::func;
    std::move_only_function<T> f2;
    f2 = std::move(f);
    assert(f2);
    LIBCPP_ASSERT(!f);
  }
  {
    decltype(&S::func) ptr       = nullptr;
    std::move_only_function<T> f = ptr;
    std::move_only_function<T> f2;
    f2 = std::move(f);
    assert(!f2);
    LIBCPP_ASSERT(!f);
  }
}

int main(int, char**) {
  call_test<void()>([]<class T> { test<T>(); });
  call_test<void(S)>([]<class T> { test_member_function_pointer<T>(); });
}
