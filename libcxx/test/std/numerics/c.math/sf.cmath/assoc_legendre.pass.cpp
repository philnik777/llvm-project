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
    assert(between(T(0.99), std::assoc_legendre(0, 0, T(0.)), T(1.01)));
    assert(between(0.99f, std::assoc_legendref(0, 0, T(0.)), 1.01f));
    assert(between(0.99l, std::assoc_legendrel(0, 0, T(0.)), 1.01l));

    assert(between(T(-0.01), std::assoc_legendre(1, 1, T(1.)), T(0.01)));
    assert(between(-0.01f, std::assoc_legendref(1, 1, T(1.)), 0.01f));
    assert(between(-0.01l, std::assoc_legendrel(1, 1, T(1.)), 0.01l));

    static_assert(std::is_same_v<decltype(std::assoc_legendre(0, 0, T(0.))), T>);
    static_assert(std::is_same_v<decltype(std::assoc_legendref(0, 0, T(0.))), float>);
    static_assert(std::is_same_v<decltype(std::assoc_legendrel(0, 0, T(0.))), long double>);

    check_no_domain_error([] { (void)std::assoc_legendre(0, 0, std::numeric_limits<T>::quiet_NaN()); });
  }
};

struct TestIntegral {
  template <class T>
  void operator()() {
    assert(between(0.99, std::assoc_legendre(0, 0, T(0.)), 1.01));
    assert(between(0.99f, std::assoc_legendref(0, 0, T(0.)), 1.01f));
    assert(between(0.99l, std::assoc_legendrel(0, 0, T(0.)), 1.01l));

    static_assert(std::is_same_v<decltype(std::assoc_legendre(0, 0, T(0.))), double>);
    static_assert(std::is_same_v<decltype(std::assoc_legendref(0, 0, T(0.))), float>);
    static_assert(std::is_same_v<decltype(std::assoc_legendrel(0, 0, T(0.))), long double>);
  }
};

int main(int, char**) {
  meta::for_each(meta::floating_point_types{}, TestFloatingPoint{});
  meta::for_each(meta::integral_types{}, TestIntegral{});

  return 0;
}
