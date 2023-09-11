//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___MATH_SPECIAL_FUNCTIONS_H
#define _LIBCPP___MATH_SPECIAL_FUNCTIONS_H

#include <__availability>
#include <__config>
#include <__type_traits/enable_if.h>
#include <__type_traits/is_arithmetic.h>
#include <cerrno>
#include <cfenv>
#include <math.h>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

#if _LIBCPP_STD_VER >= 17

_LIBCPP_BEGIN_NAMESPACE_STD

template <class _Tp>
struct __msf_result {
  bool __domain_error;
  _Tp __ret;

  operator _Tp() {
#  if math_errhandling & MATH_ERRNO
    if (__domain_error)
      errno = EDOM;
#  endif

#  if math_errhandling & MATH_ERREXCEPT
    if (__domain_error)
      feraiseexcept(FE_INVALID);
#  endif

    return __ret;
  }
};

#  define _LIBCPP_LIBRARY_MSF                                                                                          \
    [[__gnu__::__const__]] _LIBCPP_FUNC_VIS _LIBCPP_AVAILABILITY_MATHEMATICAL_SPECIAL_FUNCTIONS

#  define _LIBCPP_HEADER_MSF                                                                                           \
    _LIBCPP_NODISCARD_EXT _LIBCPP_HIDE_FROM_ABI _LIBCPP_AVAILABILITY_MATHEMATICAL_SPECIAL_FUNCTIONS

// assoc_laguerre
_LIBCPP_LIBRARY_MSF __msf_result<float> __assoc_laguerre(unsigned int, unsigned int, float) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<double> __assoc_laguerre(unsigned int, unsigned int, double) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<long double> __assoc_laguerre(unsigned int, unsigned int, long double) noexcept;

_LIBCPP_HEADER_MSF inline float assoc_laguerre(unsigned int __n, unsigned int __m, float __x) noexcept {
  return std::__assoc_laguerre(__n, __m, __x);
}

_LIBCPP_HEADER_MSF inline double assoc_laguerre(unsigned int __n, unsigned int __m, double __x) noexcept {
  return std::__assoc_laguerre(__n, __m, __x);
}

_LIBCPP_HEADER_MSF inline long double assoc_laguerre(unsigned int __n, unsigned int __m, long double __x) noexcept {
  return std::__assoc_laguerre(__n, __m, __x);
}

_LIBCPP_HEADER_MSF inline float assoc_laguerref(unsigned int __n, unsigned int __m, float __x) noexcept {
  return std::assoc_laguerre(__n, __m, __x);
}

_LIBCPP_HEADER_MSF inline long double assoc_laguerrel(unsigned int __n, unsigned int __m, long double __x) noexcept {
  return std::assoc_laguerre(__n, __m, __x);
}

template <class _Tp, enable_if_t<is_arithmetic_v<_Tp>, int> = 0>
_LIBCPP_HEADER_MSF double assoc_laguerre(unsigned int __n, unsigned int __m, _Tp __v) noexcept {
  return std::assoc_laguerre(__n, __m, static_cast<double>(__v));
}

// assoc_legendre
_LIBCPP_LIBRARY_MSF __msf_result<float> __assoc_legendre(unsigned int, unsigned int, float) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<double> __assoc_legendre(unsigned int, unsigned int, double) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<long double> __assoc_legendre(unsigned int, unsigned int, long double) noexcept;

_LIBCPP_HEADER_MSF inline float assoc_legendre(unsigned int __n, unsigned int __m, float __x) noexcept {
  return std::__assoc_legendre(__n, __m, __x);
}

_LIBCPP_HEADER_MSF inline double assoc_legendre(unsigned int __n, unsigned int __m, double __x) noexcept {
  return std::__assoc_legendre(__n, __m, __x);
}

_LIBCPP_HEADER_MSF inline long double assoc_legendre(unsigned int __n, unsigned int __m, long double __x) noexcept {
  return std::__assoc_legendre(__n, __m, __x);
}

_LIBCPP_HEADER_MSF inline float assoc_legendref(unsigned int __n, unsigned int __m, float __x) noexcept {
  return std::assoc_legendre(__n, __m, __x);
}

_LIBCPP_HEADER_MSF inline long double assoc_legendrel(unsigned int __n, unsigned int __m, long double __x) noexcept {
  return std::assoc_legendre(__n, __m, __x);
}

template <class _Tp, enable_if_t<is_arithmetic_v<_Tp>, int> = 0>
_LIBCPP_HEADER_MSF double assoc_legendre(unsigned int __n, unsigned int __m, _Tp __v) noexcept {
  return std::assoc_legendre(__n, __m, static_cast<double>(__v));
}

// beta
_LIBCPP_LIBRARY_MSF __msf_result<float> __beta(float, float) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<double> __beta(double, double) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<long double> __beta(long double, long double) noexcept;

_LIBCPP_HEADER_MSF inline float beta(float __x, float __y) noexcept { return std::__beta(__x, __y); }
_LIBCPP_HEADER_MSF inline double beta(double __x, double __y) noexcept { return std::__beta(__x, __y); }
_LIBCPP_HEADER_MSF inline long double beta(long double __x, long double __y) noexcept { return std::__beta(__x, __y); }
_LIBCPP_HEADER_MSF inline float betaf(float __x, float __y) noexcept { return std::beta(__x, __y); }
_LIBCPP_HEADER_MSF inline long double betal(long double __x, long double __y) noexcept { return std::beta(__x, __y); }

template <class _Tp, class _Up, enable_if_t<is_arithmetic_v<_Tp> && is_arithmetic_v<_Up>, int> = 0>
_LIBCPP_HEADER_MSF typename __promote<_Tp, _Up>::type beta(_Tp __x, _Up __y) noexcept {
  using __result_type = typename __promote<_Tp, _Up>::type;
  return std::beta(static_cast<__result_type>(__x), static_cast<__result_type>(__y));
}

// comp_ellint_1
_LIBCPP_LIBRARY_MSF __msf_result<float> __comp_ellint_1(float __x) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<double> __comp_ellint_1(double __x) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<long double> __comp_ellint_1(long double __x) noexcept;

_LIBCPP_HEADER_MSF inline float comp_ellint_1(float __x) noexcept { return std::__comp_ellint_1(__x); }
_LIBCPP_HEADER_MSF inline double comp_ellint_1(double __x) noexcept { return std::__comp_ellint_1(__x); }
_LIBCPP_HEADER_MSF inline long double comp_ellint_1(long double __x) noexcept { return std::__comp_ellint_1(__x); }
_LIBCPP_HEADER_MSF inline float comp_ellint_1f(float __x) noexcept { return std::comp_ellint_1(__x); }
_LIBCPP_HEADER_MSF inline long double comp_ellint_1l(long double __x) noexcept { return std::comp_ellint_1(__x); }

template <class _Tp, enable_if_t<is_arithmetic_v<_Tp>, int> = 0>
_LIBCPP_HEADER_MSF double comp_ellint_1(_Tp __x) noexcept {
  return std::comp_ellint_1(static_cast<double>(__x));
}

// comp_ellint_2
_LIBCPP_LIBRARY_MSF __msf_result<float> __comp_ellint_2(float __x) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<double> __comp_ellint_2(double __x) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<long double> __comp_ellint_2(long double __x) noexcept;

_LIBCPP_HEADER_MSF inline float comp_ellint_2(float __x) noexcept { return std::__comp_ellint_2(__x); }
_LIBCPP_HEADER_MSF inline double comp_ellint_2(double __x) noexcept { return std::__comp_ellint_2(__x); }
_LIBCPP_HEADER_MSF inline long double comp_ellint_2(long double __x) noexcept { return std::__comp_ellint_2(__x); }
_LIBCPP_HEADER_MSF inline float comp_ellint_2f(float __x) noexcept { return std::comp_ellint_2(__x); }
_LIBCPP_HEADER_MSF inline long double comp_ellint_2l(long double __x) noexcept { return std::comp_ellint_2(__x); }

template <class _Tp, enable_if_t<is_arithmetic_v<_Tp>, int> = 0>
_LIBCPP_HEADER_MSF double comp_ellint_2(_Tp __x) noexcept {
  return std::comp_ellint_2(static_cast<double>(__x));
}

// comp_ellint_3
_LIBCPP_LIBRARY_MSF __msf_result<float> __comp_ellint_3(float __x, float __y) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<double> __comp_ellint_3(double __x, double __y) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<long double> __comp_ellint_3(long double __x, long double __y) noexcept;

_LIBCPP_HEADER_MSF inline float comp_ellint_3(float __x, float __y) noexcept { return std::__comp_ellint_3(__x, __y); }

_LIBCPP_HEADER_MSF inline double comp_ellint_3(double __x, double __y) noexcept {
  return std::__comp_ellint_3(__x, __y);
}

_LIBCPP_HEADER_MSF inline long double comp_ellint_3(long double __x, long double __y) noexcept {
  return std::__comp_ellint_3(__x, __y);
}

_LIBCPP_HEADER_MSF inline float comp_ellint_3f(float __x, float __y) noexcept { return std::comp_ellint_3(__x, __y); }

_LIBCPP_HEADER_MSF inline long double comp_ellint_3l(long double __x, long double __y) noexcept {
  return std::comp_ellint_3(__x, __y);
}

template <class _Tp, class _Up, enable_if_t<is_arithmetic_v<_Tp> && is_arithmetic_v<_Up>, int> = 0>
_LIBCPP_HEADER_MSF typename __promote<_Tp, _Up>::type comp_ellint_3(_Tp __x, _Up __y) noexcept {
  using __result_type = typename __promote<_Tp, _Up>::type;
  return std::comp_ellint_3(static_cast<__result_type>(__x), static_cast<__result_type>(__y));
}

// cyl_bessel_i
_LIBCPP_LIBRARY_MSF __msf_result<float> __cyl_bessel_i(float __x, float __y) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<double> __cyl_bessel_i(double __x, double __y) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<long double> __cyl_bessel_i(long double __x, long double __y) noexcept;

_LIBCPP_HEADER_MSF inline float cyl_bessel_i(float __x, float __y) noexcept { return std::__cyl_bessel_i(__x, __y); }
_LIBCPP_HEADER_MSF inline double cyl_bessel_i(double __x, double __y) noexcept { return std::__cyl_bessel_i(__x, __y); }

_LIBCPP_HEADER_MSF inline long double cyl_bessel_i(long double __x, long double __y) noexcept {
  return std::__cyl_bessel_i(__x, __y);
}

_LIBCPP_HEADER_MSF inline float cyl_bessel_if(float __x, float __y) noexcept { return std::cyl_bessel_i(__x, __y); }

_LIBCPP_HEADER_MSF inline long double cyl_bessel_il(long double __x, long double __y) noexcept {
  return std::cyl_bessel_i(__x, __y);
}

template <class _Tp, class _Up, enable_if_t<is_arithmetic_v<_Tp> && is_arithmetic_v<_Up>, int> = 0>
_LIBCPP_HEADER_MSF typename __promote<_Tp, _Up>::type cyl_bessel_i(_Tp __x, _Up __y) noexcept {
  using __result_type = typename __promote<_Tp, _Up>::type;
  return std::cyl_bessel_i(static_cast<__result_type>(__x), static_cast<__result_type>(__y));
}

// cyl_bessel_j
_LIBCPP_LIBRARY_MSF __msf_result<float> __cyl_bessel_j(float __x, float __y) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<double> __cyl_bessel_j(double __x, double __y) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<long double> __cyl_bessel_j(long double __x, long double __y) noexcept;

_LIBCPP_HEADER_MSF inline float cyl_bessel_j(float __x, float __y) noexcept { return std::__cyl_bessel_j(__x, __y); }
_LIBCPP_HEADER_MSF inline double cyl_bessel_j(double __x, double __y) noexcept { return std::__cyl_bessel_j(__x, __y); }
_LIBCPP_HEADER_MSF inline long double cyl_bessel_j(long double __x, long double __y) noexcept {
  return std::__cyl_bessel_j(__x, __y);
}

_LIBCPP_HEADER_MSF inline float cyl_bessel_jf(float __x, float __y) noexcept { return std::cyl_bessel_j(__x, __y); }

_LIBCPP_HEADER_MSF inline long double cyl_bessel_jl(long double __x, long double __y) noexcept {
  return std::cyl_bessel_j(__x, __y);
}

template <class _Tp, class _Up, enable_if_t<is_arithmetic_v<_Tp> && is_arithmetic_v<_Up>, int> = 0>
_LIBCPP_HEADER_MSF typename __promote<_Tp, _Up>::type cyl_bessel_j(_Tp __x, _Up __y) noexcept {
  using __result_type = typename __promote<_Tp, _Up>::type;
  return std::cyl_bessel_j(static_cast<__result_type>(__x), static_cast<__result_type>(__y));
}

// cyl_bessel_k
_LIBCPP_LIBRARY_MSF __msf_result<float> __cyl_bessel_k(float __x, float __y) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<double> __cyl_bessel_k(double __x, double __y) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<long double> __cyl_bessel_k(long double __x, long double __y) noexcept;

_LIBCPP_HEADER_MSF inline float cyl_bessel_k(float __x, float __y) noexcept { return std::__cyl_bessel_k(__x, __y); }
_LIBCPP_HEADER_MSF inline double cyl_bessel_k(double __x, double __y) noexcept { return std::__cyl_bessel_k(__x, __y); }
_LIBCPP_HEADER_MSF inline long double cyl_bessel_k(long double __x, long double __y) noexcept {
  return std::__cyl_bessel_k(__x, __y);
}

_LIBCPP_HEADER_MSF inline float cyl_bessel_kf(float __x, float __y) noexcept { return std::cyl_bessel_k(__x, __y); }

_LIBCPP_HEADER_MSF inline long double cyl_bessel_kl(long double __x, long double __y) noexcept {
  return std::cyl_bessel_k(__x, __y);
}

template <class _Tp, class _Up, enable_if_t<is_arithmetic_v<_Tp> && is_arithmetic_v<_Up>, int> = 0>
_LIBCPP_HEADER_MSF typename __promote<_Tp, _Up>::type cyl_bessel_k(_Tp __x, _Up __y) noexcept {
  using __result_type = typename __promote<_Tp, _Up>::type;
  return std::cyl_bessel_k(static_cast<__result_type>(__x), static_cast<__result_type>(__y));
}

// cyl_neumann
_LIBCPP_LIBRARY_MSF __msf_result<float> __cyl_neumann(float __x, float __y) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<double> __cyl_neumann(double __x, double __y) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<long double> __cyl_neumann(long double __x, long double __y) noexcept;

_LIBCPP_HEADER_MSF inline float cyl_neumann(float __x, float __y) noexcept { return std::__cyl_neumann(__x, __y); }
_LIBCPP_HEADER_MSF inline double cyl_neumann(double __x, double __y) noexcept { return std::__cyl_neumann(__x, __y); }
_LIBCPP_HEADER_MSF inline long double cyl_neumann(long double __x, long double __y) noexcept {
  return std::__cyl_neumann(__x, __y);
}

_LIBCPP_HEADER_MSF inline float cyl_neumannf(float __x, float __y) noexcept { return std::cyl_neumann(__x, __y); }

_LIBCPP_HEADER_MSF inline long double cyl_neumannl(long double __x, long double __y) noexcept {
  return std::cyl_neumann(__x, __y);
}

template <class _Tp, class _Up, enable_if_t<is_arithmetic_v<_Tp> && is_arithmetic_v<_Up>, int> = 0>
_LIBCPP_HEADER_MSF typename __promote<_Tp, _Up>::type cyl_neumann(_Tp __x, _Up __y) noexcept {
  using __result_type = typename __promote<_Tp, _Up>::type;
  return std::cyl_neumann(static_cast<__result_type>(__x), static_cast<__result_type>(__y));
}

// ellint_1
_LIBCPP_LIBRARY_MSF __msf_result<float> __ellint_1(float __x, float __y) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<double> __ellint_1(double __x, double __y) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<long double> __ellint_1(long double __x, long double __y) noexcept;

_LIBCPP_HEADER_MSF inline float ellint_1(float __x, float __y) noexcept { return std::__ellint_1(__x, __y); }
_LIBCPP_HEADER_MSF inline double ellint_1(double __x, double __y) noexcept { return std::__ellint_1(__x, __y); }
_LIBCPP_HEADER_MSF inline long double ellint_1(long double __x, long double __y) noexcept {
  return std::__ellint_1(__x, __y);
}

_LIBCPP_HEADER_MSF inline float ellint_1f(float __x, float __y) noexcept { return std::ellint_1(__x, __y); }

_LIBCPP_HEADER_MSF inline long double ellint_1l(long double __x, long double __y) noexcept {
  return std::ellint_1(__x, __y);
}

template <class _Tp, class _Up, enable_if_t<is_arithmetic_v<_Tp> && is_arithmetic_v<_Up>, int> = 0>
_LIBCPP_HEADER_MSF typename __promote<_Tp, _Up>::type ellint_1(_Tp __x, _Up __y) noexcept {
  using __result_type = typename __promote<_Tp, _Up>::type;
  return std::ellint_1(static_cast<__result_type>(__x), static_cast<__result_type>(__y));
}

// ellint_2
_LIBCPP_LIBRARY_MSF __msf_result<float> __ellint_2(float __x, float __y) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<double> __ellint_2(double __x, double __y) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<long double> __ellint_2(long double __x, long double __y) noexcept;

_LIBCPP_HEADER_MSF inline float ellint_2(float __x, float __y) noexcept { return std::__ellint_2(__x, __y); }
_LIBCPP_HEADER_MSF inline double ellint_2(double __x, double __y) noexcept { return std::__ellint_2(__x, __y); }
_LIBCPP_HEADER_MSF inline long double ellint_2(long double __x, long double __y) noexcept {
  return std::__ellint_2(__x, __y);
}

_LIBCPP_HEADER_MSF inline float ellint_2f(float __x, float __y) noexcept { return std::ellint_2(__x, __y); }

_LIBCPP_HEADER_MSF inline long double ellint_2l(long double __x, long double __y) noexcept {
  return std::ellint_2(__x, __y);
}

template <class _Tp, class _Up, enable_if_t<is_arithmetic_v<_Tp> && is_arithmetic_v<_Up>, int> = 0>
_LIBCPP_HEADER_MSF typename __promote<_Tp, _Up>::type ellint_2(_Tp __x, _Up __y) noexcept {
  using __result_type = typename __promote<_Tp, _Up>::type;
  return std::ellint_2(static_cast<__result_type>(__x), static_cast<__result_type>(__y));
}

// ellint_3
_LIBCPP_LIBRARY_MSF __msf_result<float> __ellint_3(float __x, float __y, float __z) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<double> __ellint_3(double __x, double __y, double __z) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<long double> __ellint_3(long double __x, long double __y, long double __z) noexcept;

_LIBCPP_HEADER_MSF inline float ellint_3(float __x, float __y, float __z) noexcept {
  return std::__ellint_3(__x, __y, __z);
}

_LIBCPP_HEADER_MSF inline double ellint_3(double __x, double __y, double __z) noexcept {
  return std::__ellint_3(__x, __y, __z);
}

_LIBCPP_HEADER_MSF inline long double ellint_3(long double __x, long double __y, long double __z) noexcept {
  return std::__ellint_3(__x, __y, __z);
}

_LIBCPP_HEADER_MSF inline float ellint_3f(float __x, float __y, float __z) noexcept {
  return std::ellint_3(__x, __y, __z);
}

_LIBCPP_HEADER_MSF inline long double ellint_3l(long double __x, long double __y, long double __z) noexcept {
  return std::ellint_3(__x, __y, __z);
}

template <class _Tp,
          class _Up,
          class _Vp,
          enable_if_t<is_arithmetic_v<_Tp> && is_arithmetic_v<_Up> && is_arithmetic_v<_Vp>, int> = 0>
_LIBCPP_HEADER_MSF typename __promote<_Tp, _Up, _Vp>::type ellint_3(_Tp __x, _Up __y, _Vp __z) noexcept {
  using __result_type = typename __promote<_Tp, _Up, _Vp>::type;
  return std::ellint_3(
      static_cast<__result_type>(__x), static_cast<__result_type>(__y), static_cast<__result_type>(__z));
}

// expint
_LIBCPP_LIBRARY_MSF __msf_result<float> __expint(float __x) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<double> __expint(double __x) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<long double> __expint(long double __x) noexcept;

_LIBCPP_HEADER_MSF inline float expint(float __x) noexcept { return std::__expint(__x); }
_LIBCPP_HEADER_MSF inline double expint(double __x) noexcept { return std::__expint(__x); }
_LIBCPP_HEADER_MSF inline long double expint(long double __x) noexcept { return std::__expint(__x); }
_LIBCPP_HEADER_MSF inline float expintf(float __x) noexcept { return std::expint(__x); }
_LIBCPP_HEADER_MSF inline long double expintl(long double __x) noexcept { return std::expint(__x); }

template <class _Tp, enable_if_t<is_arithmetic_v<_Tp>, int> = 0>
_LIBCPP_HEADER_MSF double expint(_Tp __x) noexcept {
  return std::expint(static_cast<double>(__x));
}

// hermite
_LIBCPP_LIBRARY_MSF __msf_result<float> __hermite(unsigned int __n, float __x) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<double> __hermite(unsigned int __n, double __x) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<long double> __hermite(unsigned int __n, long double __x) noexcept;

_LIBCPP_HEADER_MSF inline float hermite(unsigned int __n, float __x) noexcept { return std::__hermite(__n, __x); }
_LIBCPP_HEADER_MSF inline double hermite(unsigned int __n, double __x) noexcept { return std::__hermite(__n, __x); }
_LIBCPP_HEADER_MSF inline long double hermite(unsigned int __n, long double __x) noexcept {
  return std::__hermite(__n, __x);
}

_LIBCPP_HEADER_MSF inline float hermitef(unsigned int __n, float __x) noexcept { return std::hermite(__n, __x); }

_LIBCPP_HEADER_MSF inline long double hermitel(unsigned int __n, long double __x) noexcept {
  return std::hermite(__n, __x);
}

template <class _Tp, enable_if_t<is_arithmetic_v<_Tp>, int> = 0>
_LIBCPP_HEADER_MSF double hermite(unsigned int __n, _Tp __x) noexcept {
  return std::hermite(__n, static_cast<double>(__x));
}

// laguerre
_LIBCPP_LIBRARY_MSF __msf_result<float> __laguerre(unsigned int __n, float __x) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<double> __laguerre(unsigned int __n, double __x) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<long double> __laguerre(unsigned int __n, long double __x) noexcept;

_LIBCPP_HEADER_MSF inline float laguerre(unsigned int __n, float __x) noexcept { return std::__laguerre(__n, __x); }
_LIBCPP_HEADER_MSF inline double laguerre(unsigned int __n, double __x) noexcept { return std::__laguerre(__n, __x); }
_LIBCPP_HEADER_MSF inline long double laguerre(unsigned int __n, long double __x) noexcept {
  return std::__laguerre(__n, __x);
}

_LIBCPP_HEADER_MSF inline float laguerref(unsigned int __n, float __x) noexcept { return std::laguerre(__n, __x); }

_LIBCPP_HEADER_MSF inline long double laguerrel(unsigned int __n, long double __x) noexcept {
  return std::laguerre(__n, __x);
}

template <class _Tp, enable_if_t<is_arithmetic_v<_Tp>, int> = 0>
_LIBCPP_HEADER_MSF double laguerre(unsigned int __n, _Tp __x) noexcept {
  return std::laguerre(__n, static_cast<double>(__x));
}

// legendre
_LIBCPP_LIBRARY_MSF __msf_result<float> __legendre(unsigned int __n, float __x) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<double> __legendre(unsigned int __n, double __x) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<long double> __legendre(unsigned int __n, long double __x) noexcept;

_LIBCPP_HEADER_MSF inline float legendre(unsigned int __n, float __x) noexcept { return std::__legendre(__n, __x); }
_LIBCPP_HEADER_MSF inline double legendre(unsigned int __n, double __x) noexcept { return std::__legendre(__n, __x); }
_LIBCPP_HEADER_MSF inline long double legendre(unsigned int __n, long double __x) noexcept {
  return std::__legendre(__n, __x);
}

_LIBCPP_HEADER_MSF inline float legendref(unsigned int __n, float __x) noexcept { return std::legendre(__n, __x); }

_LIBCPP_HEADER_MSF inline long double legendrel(unsigned int __n, long double __x) noexcept {
  return std::legendre(__n, __x);
}

template <class _Tp, enable_if_t<is_arithmetic_v<_Tp>, int> = 0>
_LIBCPP_HEADER_MSF double legendre(unsigned int __n, _Tp __x) noexcept {
  return std::legendre(__n, static_cast<double>(__x));
}

// riemann_zeta
_LIBCPP_LIBRARY_MSF __msf_result<float> __riemann_zeta(float __x) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<double> __riemann_zeta(double __x) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<long double> __riemann_zeta(long double __x) noexcept;

_LIBCPP_HEADER_MSF inline float riemann_zeta(float __x) noexcept { return std::__riemann_zeta(__x); }
_LIBCPP_HEADER_MSF inline double riemann_zeta(double __x) noexcept { return std::__riemann_zeta(__x); }
_LIBCPP_HEADER_MSF inline long double riemann_zeta(long double __x) noexcept { return std::__riemann_zeta(__x); }

_LIBCPP_HEADER_MSF inline float riemann_zetaf(float __x) noexcept { return std::riemann_zeta(__x); }
_LIBCPP_HEADER_MSF inline long double riemann_zetal(long double __x) noexcept { return std::riemann_zeta(__x); }

template <class _Tp, enable_if_t<is_integral_v<_Tp>, int> = 0>
_LIBCPP_HEADER_MSF double riemann_zeta(_Tp __v) noexcept {
  return std::riemann_zeta(static_cast<double>(__v));
}

// sph_bessel
_LIBCPP_LIBRARY_MSF __msf_result<float> __sph_bessel(unsigned int __n, float __x) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<double> __sph_bessel(unsigned int __n, double __x) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<long double> __sph_bessel(unsigned int __n, long double __x) noexcept;

_LIBCPP_HEADER_MSF inline float sph_bessel(unsigned int __n, float __x) noexcept { return std::__sph_bessel(__n, __x); }

_LIBCPP_HEADER_MSF inline double sph_bessel(unsigned int __n, double __x) noexcept {
  return std::__sph_bessel(__n, __x);
}
_LIBCPP_HEADER_MSF inline long double sph_bessel(unsigned int __n, long double __x) noexcept {
  return std::__sph_bessel(__n, __x);
}

_LIBCPP_HEADER_MSF inline float sph_besself(unsigned int __n, float __x) noexcept { return std::sph_bessel(__n, __x); }

_LIBCPP_HEADER_MSF inline long double sph_bessell(unsigned int __n, long double __x) noexcept {
  return std::sph_bessel(__n, __x);
}

template <class _Tp, enable_if_t<is_arithmetic_v<_Tp>, int> = 0>
_LIBCPP_HEADER_MSF double sph_bessel(unsigned int __n, _Tp __x) noexcept {
  return std::sph_bessel(__n, static_cast<double>(__x));
}

// sph_legendre
_LIBCPP_LIBRARY_MSF __msf_result<float> __sph_legendre(unsigned int __x, unsigned int __y, float __z) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<double> __sph_legendre(unsigned int __x, unsigned int __y, double __z) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<long double>
__sph_legendre(unsigned int __x, unsigned int __y, long double __z) noexcept;

_LIBCPP_HEADER_MSF inline float sph_legendre(unsigned int __x, unsigned int __y, float __z) noexcept {
  return std::__sph_legendre(__x, __y, __z);
}

_LIBCPP_HEADER_MSF inline double sph_legendre(unsigned int __x, unsigned int __y, double __z) noexcept {
  return std::__sph_legendre(__x, __y, __z);
}

_LIBCPP_HEADER_MSF inline long double sph_legendre(unsigned int __x, unsigned int __y, long double __z) noexcept {
  return std::__sph_legendre(__x, __y, __z);
}

_LIBCPP_HEADER_MSF inline float sph_legendref(unsigned int __x, unsigned int __y, float __z) noexcept {
  return std::sph_legendre(__x, __y, __z);
}

_LIBCPP_HEADER_MSF inline long double sph_legendrel(unsigned int __x, unsigned int __y, long double __z) noexcept {
  return std::sph_legendre(__x, __y, __z);
}

template <class _Tp, enable_if_t<is_arithmetic_v<_Tp>, int> = 0>
_LIBCPP_HEADER_MSF double sph_legendre(unsigned int __x, unsigned int __y, _Tp __z) noexcept {
  return std::sph_legendre(__x, __y, static_cast<double>(__z));
}

// sph_neumann
_LIBCPP_LIBRARY_MSF __msf_result<float> __sph_neumann(unsigned int __n, float __x) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<double> __sph_neumann(unsigned int __n, double __x) noexcept;
_LIBCPP_LIBRARY_MSF __msf_result<long double> __sph_neumann(unsigned int __n, long double __x) noexcept;

_LIBCPP_HEADER_MSF inline float sph_neumann(unsigned int __n, float __x) noexcept {
  return std::__sph_neumann(__n, __x);
}

_LIBCPP_HEADER_MSF inline double sph_neumann(unsigned int __n, double __x) noexcept {
  return std::__sph_neumann(__n, __x);
}

_LIBCPP_HEADER_MSF inline long double sph_neumann(unsigned int __n, long double __x) noexcept {
  return std::__sph_neumann(__n, __x);
}

_LIBCPP_HEADER_MSF inline float sph_neumannf(unsigned int __n, float __x) noexcept {
  return std::sph_neumann(__n, __x);
}

_LIBCPP_HEADER_MSF inline long double sph_neumannl(unsigned int __n, long double __x) noexcept {
  return std::sph_neumann(__n, __x);
}

template <class _Tp, enable_if_t<is_arithmetic_v<_Tp>, int> = 0>
_LIBCPP_HEADER_MSF double sph_neumann(unsigned int __n, _Tp __x) noexcept {
  return std::sph_neumann(__n, static_cast<double>(__x));
}

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP_STD_VER >= 17

#endif // _LIBCPP___MATH_SPECIAL_FUNCTIONS_H
