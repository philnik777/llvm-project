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
    assert(between(T(-1.39), std::sph_neumann(1, T(1.)), T(-1.37)));
    assert(between(-1.39f, std::sph_neumannf(1, T(1.)), -1.37f));
    assert(between(-1.39l, std::sph_neumannl(1, T(1.)), -1.37l));

    assert(between(T(-4.47), std::sph_neumann(1, T(0.5)), T(4.45)));
    assert(between(-4.47f, std::sph_neumannf(1, T(0.5)), 4.45f));
    assert(between(-4.47l, std::sph_neumannl(1, T(0.5)), 4.45l));

    static_assert(std::is_same_v<decltype(std::sph_neumann(1, T(0.))), T>);
    static_assert(std::is_same_v<decltype(std::sph_neumannf(1, T(0.))), float>);
    static_assert(std::is_same_v<decltype(std::sph_neumannl(1, T(0.))), long double>);

    check_no_domain_error([] { (void)std::sph_neumann(1, std::numeric_limits<T>::quiet_NaN()); });
  }
};

struct TestIntegral {
  template <class T>
  void operator()() {
    assert(between(-1.39, std::sph_neumann(1, T(1.)), -1.37));
    assert(between(-1.39f, std::sph_neumannf(1, T(1.)), -1.37f));
    assert(between(-1.39l, std::sph_neumannl(1, T(1.)), -1.37l));

    static_assert(std::is_same_v<decltype(std::sph_neumann(1, T(0.))), double>);
    static_assert(std::is_same_v<decltype(std::sph_neumannf(1, T(0.))), float>);
    static_assert(std::is_same_v<decltype(std::sph_neumannl(1, T(0.))), long double>);
  }
};

int main(int, char**) {
  meta::for_each(meta::floating_point_types{}, TestFloatingPoint{});
  meta::for_each(meta::integral_types{}, TestIntegral{});

  return 0;
}
