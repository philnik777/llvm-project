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
    assert(between(T(-1.47), std::riemann_zeta(T(0.5)), T(-1.45)));
    assert(between(-1.47f, std::riemann_zetaf(T(0.5)), -1.45f));
    assert(between(-1.47l, std::riemann_zetal(T(0.5)), -1.45l));

    assert(between(T(-0.51), std::riemann_zeta(T(0.)), T(-0.49)));
    assert(between(-0.51f, std::riemann_zetaf(T(0.)), -0.49f));
    assert(between(-0.51l, std::riemann_zetal(T(0.)), -0.49l));

    static_assert(std::is_same_v<decltype(std::riemann_zeta(T(0.))), T>);
    static_assert(std::is_same_v<decltype(std::riemann_zetaf(T(0.))), float>);
    static_assert(std::is_same_v<decltype(std::riemann_zetal(T(0.))), long double>);

    check_no_domain_error([] { (void)std::riemann_zeta(std::numeric_limits<T>::quiet_NaN()); });
    check_domain_error([] { (void)std::riemann_zeta(T(1.)); });
  }
};

struct TestIntegral {
  template <class T>
  void operator()() {
    assert(between(-0.51, std::riemann_zeta(T(0.)), -0.49));
    assert(between(-0.51f, std::riemann_zetaf(T(0.)), -0.49f));
    assert(between(-0.51l, std::riemann_zetal(T(0.)), -0.49l));

    static_assert(std::is_same_v<decltype(std::riemann_zeta(T(0.))), double>);
    static_assert(std::is_same_v<decltype(std::riemann_zetaf(T(0.))), float>);
    static_assert(std::is_same_v<decltype(std::riemann_zetal(T(0.))), long double>);
  }
};

int main(int, char**) {
  meta::for_each(meta::floating_point_types{}, TestFloatingPoint{});
  meta::for_each(meta::integral_types{}, TestIntegral{});

  return 0;
}
