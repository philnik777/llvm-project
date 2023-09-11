//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include <__config>
#include <boost/math/special_functions.hpp>
#include <cerrno>
#include <cmath>
#include <optional>
#include <type_traits>

_LIBCPP_BEGIN_NAMESPACE_STD

namespace {
template <class Ret>
optional<Ret> check_nan() {
  return nullopt;
}

template <class Ret, class Arg, class... Args>
optional<Ret> check_nan(Arg arg, Args... args) {
  if constexpr (is_floating_point_v<Arg>)
    if (std::isnan(arg))
      return arg;
  return check_nan<Ret>(args...);
}

template <class Func, class... Args, class Ret = std::invoke_result_t<Func, Args...>>
auto invoke_boost_math(Func f, Args... args) -> __msf_result<Ret> {
  if (auto maybe_nan = check_nan<Ret>(args...); maybe_nan.has_value())
    return {false, *maybe_nan};

  try {
    return {false, f(args...)};
  } catch (...) {
    return {true, numeric_limits<Ret>::quiet_NaN()};
  }
}
} // namespace

__msf_result<float> __assoc_laguerre(unsigned int n, unsigned int m, float x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::laguerre(args...); }, n, m, x);
}

__msf_result<double> __assoc_laguerre(unsigned int n, unsigned int m, double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::laguerre(args...); }, n, m, x);
}

__msf_result<long double> __assoc_laguerre(unsigned int n, unsigned int m, long double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::laguerre(args...); }, n, m, x);
}

__msf_result<float> __assoc_legendre(unsigned int n, unsigned int m, float x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::legendre_p(args...); }, n, m, x);
}

__msf_result<double> __assoc_legendre(unsigned int n, unsigned int m, double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::legendre_p(args...); }, n, m, x);
}

__msf_result<long double> __assoc_legendre(unsigned int n, unsigned int m, long double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::legendre_p(args...); }, n, m, x);
}

__msf_result<float> __beta(float x, float y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::beta(args...); }, x, y);
}

__msf_result<double> __beta(double x, double y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::beta(args...); }, x, y);
}

__msf_result<long double> __beta(long double x, long double y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::beta(args...); }, x, y);
}

__msf_result<float> __comp_ellint_1(float x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::ellint_1(args...); }, x);
}

__msf_result<double> __comp_ellint_1(double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::ellint_1(args...); }, x);
}

__msf_result<long double> __comp_ellint_1(long double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::ellint_1(args...); }, x);
}

__msf_result<float> __comp_ellint_2(float x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::ellint_2(args...); }, x);
}

__msf_result<double> __comp_ellint_2(double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::ellint_2(args...); }, x);
}

__msf_result<long double> __comp_ellint_2(long double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::ellint_2(args...); }, x);
}

__msf_result<float> __comp_ellint_3(float x, float y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::ellint_3(args...); }, x, y);
}

__msf_result<double> __comp_ellint_3(double x, double y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::ellint_3(args...); }, x, y);
}

__msf_result<long double> __comp_ellint_3(long double x, long double y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::ellint_3(args...); }, x, y);
}

__msf_result<float> __cyl_bessel_i(float x, float y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::cyl_bessel_i(args...); }, x, y);
}

__msf_result<double> __cyl_bessel_i(double x, double y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::cyl_bessel_i(args...); }, x, y);
}

__msf_result<long double> __cyl_bessel_i(long double x, long double y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::cyl_bessel_i(args...); }, x, y);
}

__msf_result<float> __cyl_bessel_j(float x, float y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::cyl_bessel_j(args...); }, x, y);
}

__msf_result<double> __cyl_bessel_j(double x, double y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::cyl_bessel_j(args...); }, x, y);
}

__msf_result<long double> __cyl_bessel_j(long double x, long double y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::cyl_bessel_j(args...); }, x, y);
}

__msf_result<float> __cyl_bessel_k(float x, float y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::cyl_bessel_k(args...); }, x, y);
}

__msf_result<double> __cyl_bessel_k(double x, double y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::cyl_bessel_k(args...); }, x, y);
}

__msf_result<long double> __cyl_bessel_k(long double x, long double y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::cyl_bessel_k(args...); }, x, y);
}

__msf_result<float> __cyl_neumann(float x, float y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::cyl_neumann(args...); }, x, y);
}

__msf_result<double> __cyl_neumann(double x, double y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::cyl_neumann(args...); }, x, y);
}

__msf_result<long double> __cyl_neumann(long double x, long double y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::cyl_neumann(args...); }, x, y);
}

__msf_result<float> __ellint_1(float x, float y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::ellint_1(args...); }, x, y);
}

__msf_result<double> __ellint_1(double x, double y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::ellint_1(args...); }, x, y);
}

__msf_result<long double> __ellint_1(long double x, long double y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::ellint_1(args...); }, x, y);
}

__msf_result<float> __ellint_2(float x, float y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::ellint_2(args...); }, x, y);
}

__msf_result<double> __ellint_2(double x, double y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::ellint_2(args...); }, x, y);
}

__msf_result<long double> __ellint_2(long double x, long double y) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::ellint_2(args...); }, x, y);
}

__msf_result<float> __ellint_3(float x, float y, float z) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::ellint_3(args...); }, x, y, z);
}

__msf_result<double> __ellint_3(double x, double y, double z) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::ellint_3(args...); }, x, y, z);
}

__msf_result<long double> __ellint_3(long double x, long double y, long double z) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::ellint_3(args...); }, x, y, z);
}

__msf_result<float> __expint(float x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::expint(args...); }, x);
}

__msf_result<double> __expint(double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::expint(args...); }, x);
}

__msf_result<long double> __expint(long double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::expint(args...); }, x);
}

__msf_result<float> __hermite(unsigned int n, float x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::hermite(args...); }, n, x);
}

__msf_result<double> __hermite(unsigned int n, double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::hermite(args...); }, n, x);
}

__msf_result<long double> __hermite(unsigned int n, long double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::hermite(args...); }, n, x);
}

__msf_result<float> __laguerre(unsigned int n, float x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::laguerre(args...); }, n, x);
}

__msf_result<double> __laguerre(unsigned int n, double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::laguerre(args...); }, n, x);
}

__msf_result<long double> __laguerre(unsigned int n, long double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::laguerre(args...); }, n, x);
}

__msf_result<float> __legendre(unsigned int n, float x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::legendre_p(args...); }, n, x);
}

__msf_result<double> __legendre(unsigned int n, double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::legendre_p(args...); }, n, x);
}

__msf_result<long double> __legendre(unsigned int n, long double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::legendre_p(args...); }, n, x);
}

__msf_result<float> __riemann_zeta(float x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::zeta(args...); }, x);
}

__msf_result<double> __riemann_zeta(double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::zeta(args...); }, x);
}

__msf_result<long double> __riemann_zeta(long double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::zeta(args...); }, x);
}

__msf_result<float> __sph_bessel(unsigned int n, float x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::sph_bessel(args...); }, n, x);
}

__msf_result<double> __sph_bessel(unsigned int n, double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::sph_bessel(args...); }, n, x);
}

__msf_result<long double> __sph_bessel(unsigned int n, long double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::sph_bessel(args...); }, n, x);
}

__msf_result<float> __sph_legendre(unsigned int n, unsigned int m, float x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::spherical_harmonic_r(args..., 0.f); }, n, m, x);
}

__msf_result<double> __sph_legendre(unsigned int n, unsigned int m, double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::spherical_harmonic_r(args..., 0.0); }, n, m, x);
}

__msf_result<long double> __sph_legendre(unsigned int n, unsigned int m, long double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::spherical_harmonic_r(args..., 0.l); }, n, m, x);
}

__msf_result<float> __sph_neumann(unsigned int m, float x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::sph_neumann(args...); }, m, x);
}

__msf_result<double> __sph_neumann(unsigned int m, double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::sph_neumann(args...); }, m, x);
}

__msf_result<long double> __sph_neumann(unsigned int m, long double x) noexcept {
  return invoke_boost_math([&](auto... args) { return boost::math::sph_neumann(args...); }, m, x);
}

_LIBCPP_END_NAMESPACE_STD
