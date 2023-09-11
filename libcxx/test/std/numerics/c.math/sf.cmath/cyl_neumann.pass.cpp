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
    assert(between(T(-0.79), std::cyl_neumann(T(1.), T(1.)), T(-0.77)));
    assert(between(-0.79f, std::cyl_neumannf(T(1.), T(1.)), -0.77f));
    assert(between(-0.79l, std::cyl_neumannl(T(1.), T(1.)), -0.77l));

    assert(between(T(-0.63), std::cyl_neumann(T(2.0), T(2.0)), T(-0.61)));
    assert(between(-0.63f, std::cyl_neumannf(T(2.0), T(2.0)), -0.61f));
    assert(between(-0.63l, std::cyl_neumannl(T(2.0), T(2.0)), -0.61l));

    static_assert(std::is_same_v<decltype(std::cyl_neumann(T(0.), T(0.))), T>);
    static_assert(std::is_same_v<decltype(std::cyl_neumannf(T(0.), T(0.))), float>);
    static_assert(std::is_same_v<decltype(std::cyl_neumannl(T(0.), T(0.))), long double>);

    check_no_domain_error([] { (void)std::cyl_neumann(T(0.), std::numeric_limits<T>::quiet_NaN()); });
    check_no_domain_error([] { (void)std::cyl_neumann(std::numeric_limits<T>::quiet_NaN(), T(0.)); });
    check_no_domain_error([] {
      (void)std::cyl_neumann(std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN());
    });
    check_domain_error([] { (void)std::cyl_neumann(T(0.), T(0.)); });
  }
};

struct TestIntegral {
  template <class T>
  void operator()() {
    assert(between(-0.79, std::cyl_neumann(T(1.), T(1.)), -0.77));
    assert(between(-0.79f, std::cyl_neumannf(T(1.), T(1.)), -0.77f));
    assert(between(-0.79l, std::cyl_neumannl(T(1.), T(1.)), -0.77l));

    static_assert(std::is_same_v<decltype(std::cyl_neumann(T(0.), T(0.))), double>);
    static_assert(std::is_same_v<decltype(std::cyl_neumannf(T(0.), T(0.))), float>);
    static_assert(std::is_same_v<decltype(std::cyl_neumannl(T(0.), T(0.))), long double>);
  }
};

int main(int, char**) {
  meta::for_each(meta::floating_point_types{}, TestFloatingPoint{});
  meta::for_each(meta::integral_types{}, TestIntegral{});

  return 0;
}
