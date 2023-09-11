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
    assert(between(T(0.83), std::ellint_2(T(1.), T(1.)), T(0.85)));
    assert(between(0.83f, std::ellint_2f(T(1.), T(1.)), 0.85f));
    assert(between(0.83l, std::ellint_2l(T(1.), T(1.)), 0.85l));

    assert(between(T(-0.01), std::ellint_2(T(0.0), T(0.0)), T(0.01)));
    assert(between(-0.01f, std::ellint_2f(T(0.0), T(0.0)), 0.01f));
    assert(between(-0.01l, std::ellint_2l(T(0.0), T(0.0)), 0.01l));

    static_assert(std::is_same_v<decltype(std::ellint_2(T(0.), T(0.))), T>);
    static_assert(std::is_same_v<decltype(std::ellint_2f(T(0.), T(0.))), float>);
    static_assert(std::is_same_v<decltype(std::ellint_2l(T(0.), T(0.))), long double>);

    check_no_domain_error([] { (void)std::ellint_2(T(0.), std::numeric_limits<T>::quiet_NaN()); });
    check_no_domain_error([] { (void)std::ellint_2(std::numeric_limits<T>::quiet_NaN(), T(0.)); });
    check_no_domain_error([] {
      (void)std::ellint_2(std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN());
    });
    check_domain_error([] { (void)std::ellint_2(T(2.), T(2.)); });
  }
};

struct TestIntegral {
  template <class T>
  void operator()() {
    assert(between(0.83, std::ellint_2(T(1.), T(1.)), 0.85));
    assert(between(0.83f, std::ellint_2f(T(1.), T(1.)), 0.85f));
    assert(between(0.83l, std::ellint_2l(T(1.), T(1.)), 0.85l));

    assert(between(-0.01, std::ellint_2(T(0.0), T(0.0)), 0.01));
    assert(between(-0.01f, std::ellint_2f(T(0.0), T(0.0)), 0.01f));
    assert(between(-0.01l, std::ellint_2l(T(0.0), T(0.0)), 0.01l));

    static_assert(std::is_same_v<decltype(std::ellint_2(T(0.), T(0.))), double>);
    static_assert(std::is_same_v<decltype(std::ellint_2f(T(0.), T(0.))), float>);
    static_assert(std::is_same_v<decltype(std::ellint_2l(T(0.), T(0.))), long double>);
  }
};

int main(int, char**) {
  meta::for_each(meta::floating_point_types{}, TestFloatingPoint{});
  meta::for_each(meta::integral_types{}, TestIntegral{});

  return 0;
}
