//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03, c++11, c++14

#include <cassert>
#include <cerrno>
#include <cfenv>
#include <cmath>

#include "common.h"
#include "type_algorithms.h"

struct TestFloatingPoint {
  template <class T>
  void operator()() {
    assert(between(T(1.88), std::expint(T(1.)), T(1.90)));
    assert(between(1.88f, std::expintf(T(1.)), 1.90f));
    assert(between(1.88l, std::expintl(T(1.)), 1.90l));

    assert(between(T(0.45), std::expint(T(0.5)), T(0.47)));
    assert(between(0.45f, std::expintf(T(0.5)), 0.47f));
    assert(between(0.45l, std::expintl(T(0.5)), 0.47l));

    static_assert(std::is_same_v<decltype(std::expint(T(0.))), T>);
    static_assert(std::is_same_v<decltype(std::expintf(T(0.))), float>);
    static_assert(std::is_same_v<decltype(std::expintl(T(0.))), long double>);

    check_no_domain_error([] { (void)std::expint(std::numeric_limits<T>::quiet_NaN()); });
    check_domain_error([] { (void)std::expint(T(0.)); });
  }
};

struct TestIntegral {
  template <class T>
  void operator()() {
    assert(between(1.88, std::expint(T(1.)), 1.90));
    assert(between(1.88f, std::expintf(T(1.)), 1.90f));
    assert(between(1.88l, std::expintl(T(1.)), 1.90l));

    static_assert(std::is_same_v<decltype(std::expint(T(0.))), double>);
    static_assert(std::is_same_v<decltype(std::expintf(T(0.))), float>);
    static_assert(std::is_same_v<decltype(std::expintl(T(0.))), long double>);
  }
};

int main(int, char**) {
  meta::for_each(meta::floating_point_types{}, TestFloatingPoint{});
  meta::for_each(meta::integral_types{}, TestIntegral{});

  return 0;
}
