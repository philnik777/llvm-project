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
    assert(between(T(1.56), std::comp_ellint_3(T(0.), T(0.)), T(1.58)));
    assert(between(1.56f, std::comp_ellint_3f(T(0.), T(0.)), 1.58f));
    assert(between(1.56l, std::comp_ellint_3l(T(0.), T(0.)), 1.58l));

    assert(between(T(1.34), std::comp_ellint_3(T(0.8), T(-1.)), T(1.36)));
    assert(between(1.34f, std::comp_ellint_3f(T(0.8), T(-1.)), 1.36f));
    assert(between(1.34l, std::comp_ellint_3l(T(0.8), T(-1.)), 1.36l));

    static_assert(std::is_same_v<decltype(std::comp_ellint_3(T(0.), T(0.))), T>);
    static_assert(std::is_same_v<decltype(std::comp_ellint_3f(T(0.), T(0.))), float>);
    static_assert(std::is_same_v<decltype(std::comp_ellint_3l(T(0.), T(0.))), long double>);

    check_no_domain_error([] { (void)std::comp_ellint_3(T(0.), std::numeric_limits<T>::quiet_NaN()); });
    check_no_domain_error([] { (void)std::comp_ellint_3(std::numeric_limits<T>::quiet_NaN(), T(0.)); });
    check_no_domain_error([] {
      (void)std::comp_ellint_3(std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN());
    });
  }
};

struct TestIntegral {
  template <class T>
  void operator()() {
    assert(between(1.56, std::comp_ellint_3(T(0.), T(0.)), 1.58));
    assert(between(1.56f, std::comp_ellint_3f(T(0.), T(0.)), 1.58f));
    assert(between(1.56l, std::comp_ellint_3l(T(0.), T(0.)), 1.58l));

    static_assert(std::is_same_v<decltype(std::comp_ellint_3(T(0.), T(0.))), double>);
    static_assert(std::is_same_v<decltype(std::comp_ellint_3f(T(0.), T(0.))), float>);
    static_assert(std::is_same_v<decltype(std::comp_ellint_3l(T(0.), T(0.))), long double>);
  }
};

int main(int, char**) {
  meta::for_each(meta::floating_point_types{}, TestFloatingPoint{});
  meta::for_each(meta::integral_types{}, TestIntegral{});

  return 0;
}
