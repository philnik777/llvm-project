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
    assert(between(T(0.99), std::cyl_bessel_j(T(0.), T(0.)), T(1.01)));
    assert(between(0.99f, std::cyl_bessel_jf(T(0.), T(0.)), 1.01f));
    assert(between(0.99l, std::cyl_bessel_jl(T(0.), T(0.)), 1.01l));

    assert(between(T(0.44), std::cyl_bessel_j(T(1.), T(1.)), T(0.46)));
    assert(between(0.44f, std::cyl_bessel_jf(T(1.), T(1.)), 0.46f));
    assert(between(0.44l, std::cyl_bessel_jl(T(1.), T(1.)), 0.46l));

    static_assert(std::is_same_v<decltype(std::cyl_bessel_j(T(0.), T(0.))), T>);
    static_assert(std::is_same_v<decltype(std::cyl_bessel_jf(T(0.), T(0.))), float>);
    static_assert(std::is_same_v<decltype(std::cyl_bessel_jl(T(0.), T(0.))), long double>);

    check_no_domain_error([] { (void)std::cyl_bessel_j(T(0.), std::numeric_limits<T>::quiet_NaN()); });
    check_no_domain_error([] { (void)std::cyl_bessel_j(std::numeric_limits<T>::quiet_NaN(), T(0.)); });
    check_no_domain_error([] {
      (void)std::cyl_bessel_j(std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN());
    });
  }
};

struct TestIntegral {
  template <class T>
  void operator()() {
    assert(between(0.99, std::cyl_bessel_j(T(0.), T(0.)), 1.01));
    assert(between(0.99f, std::cyl_bessel_jf(T(0.), T(0.)), 1.01f));
    assert(between(0.99l, std::cyl_bessel_jl(T(0.), T(0.)), 1.01l));

    assert(between(0.44, std::cyl_bessel_j(T(1.), T(1.)), 0.46));
    assert(between(0.44f, std::cyl_bessel_jf(T(1.), T(1.)), 0.46f));
    assert(between(0.44l, std::cyl_bessel_jl(T(1.), T(1.)), 0.46l));

    static_assert(std::is_same_v<decltype(std::cyl_bessel_j(T(0.), T(0.))), double>);
    static_assert(std::is_same_v<decltype(std::cyl_bessel_jf(T(0.), T(0.))), float>);
    static_assert(std::is_same_v<decltype(std::cyl_bessel_jl(T(0.), T(0.))), long double>);
  }
};

int main(int, char**) {
  meta::for_each(meta::floating_point_types{}, TestFloatingPoint{});
  meta::for_each(meta::integral_types{}, TestIntegral{});

  return 0;
}
