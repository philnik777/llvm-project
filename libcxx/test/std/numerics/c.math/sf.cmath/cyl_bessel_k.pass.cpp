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
    assert(between(T(0.60), std::cyl_bessel_k(T(1.), T(1.)), T(0.62)));
    assert(between(0.60f, std::cyl_bessel_kf(T(1.), T(1.)), 0.62f));
    assert(between(0.60l, std::cyl_bessel_kl(T(1.), T(1.)), 0.62l));

    assert(between(T(1.07), std::cyl_bessel_k(T(0.5), T(0.5)), T(1.09)));
    assert(between(1.07f, std::cyl_bessel_kf(T(0.5), T(0.5)), 1.09f));
    assert(between(1.07l, std::cyl_bessel_kl(T(0.5), T(0.5)), 1.09l));

    static_assert(std::is_same_v<decltype(std::cyl_bessel_k(T(0.), T(0.))), T>);
    static_assert(std::is_same_v<decltype(std::cyl_bessel_kf(T(0.), T(0.))), float>);
    static_assert(std::is_same_v<decltype(std::cyl_bessel_kl(T(0.), T(0.))), long double>);

    check_no_domain_error([] { (void)std::cyl_bessel_k(T(0.), std::numeric_limits<T>::quiet_NaN()); });
    check_no_domain_error([] { (void)std::cyl_bessel_k(std::numeric_limits<T>::quiet_NaN(), T(0.)); });
    check_no_domain_error([] {
      (void)std::cyl_bessel_k(std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN());
    });
    check_domain_error([] { (void)std::cyl_bessel_k(T(0.), T(0.)); });
  }
};

struct TestIntegral {
  template <class T>
  void operator()() {
    assert(between(0.60, std::cyl_bessel_k(T(1.), T(1.)), 0.62));
    assert(between(0.60f, std::cyl_bessel_kf(T(1.), T(1.)), 0.62f));
    assert(between(0.60l, std::cyl_bessel_kl(T(1.), T(1.)), 0.62l));

    static_assert(std::is_same_v<decltype(std::cyl_bessel_k(T(0.), T(0.))), double>);
    static_assert(std::is_same_v<decltype(std::cyl_bessel_kf(T(0.), T(0.))), float>);
    static_assert(std::is_same_v<decltype(std::cyl_bessel_kl(T(0.), T(0.))), long double>);
  }
};

int main(int, char**) {
  meta::for_each(meta::floating_point_types{}, TestFloatingPoint{});
  meta::for_each(meta::integral_types{}, TestIntegral{});

  return 0;
}
