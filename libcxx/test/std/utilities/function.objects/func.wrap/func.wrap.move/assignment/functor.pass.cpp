//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03, c++11, c++14, c++17, c++20

#include <cassert>
#include <concepts>
#include <functional>

#include "test_macros.h"
#include "../common.h"

template <class T>
void test() {
  static_assert(!std::is_nothrow_assignable_v<std::move_only_function<T>&, NonTrivial>);
  {
    std::move_only_function<T> f;
    std::same_as<std::move_only_function<T>&> decltype(auto) ret = (f = &call_func);
    assert(&ret == &f);
    assert(f);
  }
  {
    std::move_only_function<T> f;
    decltype(&call_func) ptr                                     = nullptr;
    std::same_as<std::move_only_function<T>&> decltype(auto) ret = (f = ptr);
    assert(&ret == &f);
    assert(!f);
  }
  {
    std::move_only_function<T> f;
    std::same_as<std::move_only_function<T>&> decltype(auto) ret = (f = TriviallyDestructible{});
    assert(&ret == &f);
    assert(f);
  }
  {
    std::move_only_function<T> f;
    std::same_as<std::move_only_function<T>&> decltype(auto) ret = (f = TriviallyDestructibleTooLarge{});
    assert(&ret == &f);
    assert(f);
  }
  {
    std::move_only_function<T> f;
    std::same_as<std::move_only_function<T>&> decltype(auto) ret = (f = NonTrivial{});
    assert(&ret == &f);
    assert(f);
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
  }
  {
    decltype(&S::func) ptr       = nullptr;
    std::move_only_function<T> f = ptr;
    std::move_only_function<T> f2;
    f2 = std::move(f);
    assert(!f2);
  }
}

int main(int, char**) {
  call_test<void()>([]<class T> { test<T>(); });
  call_test<void(S)>([]<class T> { test_member_function_pointer<T>(); });
}
