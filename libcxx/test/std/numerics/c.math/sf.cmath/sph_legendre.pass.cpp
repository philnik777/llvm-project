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
    assert(between(T(-0.30), std::sph_legendre(1, 1, T(1.)), T(-0.28)));
    assert(between(-0.30f, std::sph_legendref(1, 1, T(1.)), -0.28f));
    assert(between(-0.30l, std::sph_legendrel(1, 1, T(1.)), -0.28l));

    assert(between(T(-0.17), std::sph_legendre(1, 1, T(0.5)), T(-0.15)));
    assert(between(-0.17f, std::sph_legendref(1, 1, T(0.5)), -0.15f));
    assert(between(-0.17l, std::sph_legendrel(1, 1, T(0.5)), -0.15l));

    static_assert(std::is_same_v<decltype(std::sph_legendre(1, 1, T(0.))), T>);
    static_assert(std::is_same_v<decltype(std::sph_legendref(1, 1, T(0.))), float>);
    static_assert(std::is_same_v<decltype(std::sph_legendrel(1, 1, T(0.))), long double>);

    check_no_domain_error([] { (void)std::sph_legendre(1, 1, std::numeric_limits<T>::quiet_NaN()); });
  }
};

struct TestIntegral {
  template <class T>
  void operator()() {
    assert(between(-0.30, std::sph_legendre(1, 1, T(1.)), -0.28));
    assert(between(-0.30f, std::sph_legendref(1, 1, T(1.)), -0.28f));
    assert(between(-0.30l, std::sph_legendrel(1, 1, T(1.)), -0.28l));

    static_assert(std::is_same_v<decltype(std::sph_legendre(1, 1, T(0.))), double>);
    static_assert(std::is_same_v<decltype(std::sph_legendref(1, 1, T(0.))), float>);
    static_assert(std::is_same_v<decltype(std::sph_legendrel(1, 1, T(0.))), long double>);
  }
};

int main(int, char**) {
  meta::for_each(meta::floating_point_types{}, TestFloatingPoint{});
  meta::for_each(meta::integral_types{}, TestIntegral{});

  return 0;
}
