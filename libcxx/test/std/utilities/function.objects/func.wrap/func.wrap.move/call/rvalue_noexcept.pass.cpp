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
#include <utility>

#include "test_macros.h"
#include "../common.h"

struct S {
  void func() && noexcept {}
};

static_assert(!std::is_invocable_v<std::move_only_function<void() && noexcept>&>);
static_assert(std::is_invocable_v<std::move_only_function<void() && noexcept>>);
static_assert(std::is_invocable_v<std::move_only_function<void() && noexcept>&&>);
static_assert(!std::is_invocable_v<std::move_only_function<void() && noexcept> const&>);
static_assert(!std::is_invocable_v<std::move_only_function<void() && noexcept> const >);
static_assert(!std::is_invocable_v<std::move_only_function<void() && noexcept> const&&>);

void test() {
  {
    called                                       = false;
    std::move_only_function<void()&& noexcept> f = &call_func;
    std::move(f)();
    assert(called);
  }
  {
    called                                       = false;
    std::move_only_function<void()&& noexcept> f = TriviallyDestructible{};
    std::move(f)();
    assert(called);
  }
  {
    called                                       = false;
    std::move_only_function<void()&& noexcept> f = TriviallyDestructibleTooLarge{};
    std::move(f)();
    assert(called);
  }
  {
    called                                       = false;
    std::move_only_function<void()&& noexcept> f = NonTrivial{};
    std::move(f)();
    assert(called);
  }
  {
    std::move_only_function<void(S)&& noexcept> f = &S::func;
    assert(f);
  }
  {
    decltype(&S::func) ptr                        = nullptr;
    std::move_only_function<void(S)&& noexcept> f = ptr;
    assert(!f);
  }
  {
    CallType type;
    std::move_only_function<void()&& noexcept> f = CallTypeCheckerNoexcept{&type};
    type                                         = CallType::None;
    std::move(f)();
    assert(type == CallType::RValue);
  }
}

void test_return() {
  {
    called                                         = false;
    std::move_only_function<int(int)&& noexcept> f = &get_val;
    assert(std::move(f)(3) == 3);
    assert(!called);
  }
  {
    called                                         = false;
    std::move_only_function<int(int)&& noexcept> f = TriviallyDestructible{};
    assert(std::move(f)(3) == 3);
    assert(!called);
  }
  {
    called                                         = false;
    std::move_only_function<int(int)&& noexcept> f = TriviallyDestructibleTooLarge{};
    assert(std::move(f)(3) == 3);
    assert(!called);
  }
  {
    called                                         = false;
    std::move_only_function<int(int)&& noexcept> f = NonTrivial{};
    assert(std::move(f)(3) == 3);
    assert(!called);
  }
}

int main(int, char**) {
  test();
  test_return();

  return 0;
}
