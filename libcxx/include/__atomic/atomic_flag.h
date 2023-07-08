//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___ATOMIC_ATOMIC_FLAG_H
#define _LIBCPP___ATOMIC_ATOMIC_FLAG_H

#include <__atomic/atomic_sync.h>
#include <__atomic/contention_t.h>
#include <__atomic/cxx_atomic_impl.h>
#include <__atomic/memory_order.h>
#include <__chrono/duration.h>
#include <__config>
#include <__threading_support>
#include <cstdint>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

struct atomic_flag
{
    __cxx_atomic_impl<_LIBCPP_ATOMIC_FLAG_TYPE> __a_;

    _LIBCPP_HIDE_FROM_ABI
    bool test(memory_order __m = memory_order_seq_cst) const volatile noexcept
        {return _LIBCPP_ATOMIC_FLAG_TYPE(true) == __cxx_atomic_load(&__a_, __m);}
    _LIBCPP_HIDE_FROM_ABI
    bool test(memory_order __m = memory_order_seq_cst) const noexcept
        {return _LIBCPP_ATOMIC_FLAG_TYPE(true) == __cxx_atomic_load(&__a_, __m);}

    _LIBCPP_HIDE_FROM_ABI
    bool test_and_set(memory_order __m = memory_order_seq_cst) volatile noexcept
        {return __cxx_atomic_exchange(&__a_, _LIBCPP_ATOMIC_FLAG_TYPE(true), __m);}
    _LIBCPP_HIDE_FROM_ABI
    bool test_and_set(memory_order __m = memory_order_seq_cst) noexcept
        {return __cxx_atomic_exchange(&__a_, _LIBCPP_ATOMIC_FLAG_TYPE(true), __m);}
    _LIBCPP_HIDE_FROM_ABI
    void clear(memory_order __m = memory_order_seq_cst) volatile noexcept
        {__cxx_atomic_store(&__a_, _LIBCPP_ATOMIC_FLAG_TYPE(false), __m);}
    _LIBCPP_HIDE_FROM_ABI
    void clear(memory_order __m = memory_order_seq_cst) noexcept
        {__cxx_atomic_store(&__a_, _LIBCPP_ATOMIC_FLAG_TYPE(false), __m);}

    _LIBCPP_AVAILABILITY_SYNC _LIBCPP_HIDE_FROM_ABI
    void wait(bool __v, memory_order __m = memory_order_seq_cst) const volatile noexcept
        {__cxx_atomic_wait(&__a_, _LIBCPP_ATOMIC_FLAG_TYPE(__v), __m);}
    _LIBCPP_AVAILABILITY_SYNC _LIBCPP_HIDE_FROM_ABI
    void wait(bool __v, memory_order __m = memory_order_seq_cst) const noexcept
        {__cxx_atomic_wait(&__a_, _LIBCPP_ATOMIC_FLAG_TYPE(__v), __m);}
    _LIBCPP_AVAILABILITY_SYNC _LIBCPP_HIDE_FROM_ABI
    void notify_one() volatile noexcept
        {__cxx_atomic_notify_one(&__a_);}
    _LIBCPP_AVAILABILITY_SYNC _LIBCPP_HIDE_FROM_ABI
    void notify_one() noexcept
        {__cxx_atomic_notify_one(&__a_);}
    _LIBCPP_AVAILABILITY_SYNC _LIBCPP_HIDE_FROM_ABI
    void notify_all() volatile noexcept
        {__cxx_atomic_notify_all(&__a_);}
    _LIBCPP_AVAILABILITY_SYNC _LIBCPP_HIDE_FROM_ABI
    void notify_all() noexcept
        {__cxx_atomic_notify_all(&__a_);}

#if _LIBCPP_STD_VER >= 20
    _LIBCPP_HIDE_FROM_ABI constexpr
    atomic_flag() noexcept : __a_(false) {}
#else
    atomic_flag() noexcept = default;
#endif

    _LIBCPP_HIDE_FROM_ABI constexpr
    atomic_flag(bool __b) noexcept : __a_(__b) {} // EXTENSION

    atomic_flag(const atomic_flag&) = delete;
    atomic_flag& operator=(const atomic_flag&) = delete;
    atomic_flag& operator=(const atomic_flag&) volatile = delete;

};

inline _LIBCPP_HIDE_FROM_ABI
bool
atomic_flag_test(const volatile atomic_flag* __o) noexcept
{
    return __o->test();
}

inline _LIBCPP_HIDE_FROM_ABI
bool
atomic_flag_test(const atomic_flag* __o) noexcept
{
    return __o->test();
}

inline _LIBCPP_HIDE_FROM_ABI
bool
atomic_flag_test_explicit(const volatile atomic_flag* __o, memory_order __m) noexcept
{
    return __o->test(__m);
}

inline _LIBCPP_HIDE_FROM_ABI
bool
atomic_flag_test_explicit(const atomic_flag* __o, memory_order __m) noexcept
{
    return __o->test(__m);
}

inline _LIBCPP_HIDE_FROM_ABI
bool
atomic_flag_test_and_set(volatile atomic_flag* __o) noexcept
{
    return __o->test_and_set();
}

inline _LIBCPP_HIDE_FROM_ABI
bool
atomic_flag_test_and_set(atomic_flag* __o) noexcept
{
    return __o->test_and_set();
}

inline _LIBCPP_HIDE_FROM_ABI
bool
atomic_flag_test_and_set_explicit(volatile atomic_flag* __o, memory_order __m) noexcept
{
    return __o->test_and_set(__m);
}

inline _LIBCPP_HIDE_FROM_ABI
bool
atomic_flag_test_and_set_explicit(atomic_flag* __o, memory_order __m) noexcept
{
    return __o->test_and_set(__m);
}

inline _LIBCPP_HIDE_FROM_ABI
void
atomic_flag_clear(volatile atomic_flag* __o) noexcept
{
    __o->clear();
}

inline _LIBCPP_HIDE_FROM_ABI
void
atomic_flag_clear(atomic_flag* __o) noexcept
{
    __o->clear();
}

inline _LIBCPP_HIDE_FROM_ABI
void
atomic_flag_clear_explicit(volatile atomic_flag* __o, memory_order __m) noexcept
{
    __o->clear(__m);
}

inline _LIBCPP_HIDE_FROM_ABI
void
atomic_flag_clear_explicit(atomic_flag* __o, memory_order __m) noexcept
{
    __o->clear(__m);
}

inline _LIBCPP_HIDE_FROM_ABI _LIBCPP_AVAILABILITY_SYNC
void
atomic_flag_wait(const volatile atomic_flag* __o, bool __v) noexcept
{
    __o->wait(__v);
}

inline _LIBCPP_HIDE_FROM_ABI _LIBCPP_AVAILABILITY_SYNC
void
atomic_flag_wait(const atomic_flag* __o, bool __v) noexcept
{
    __o->wait(__v);
}

inline _LIBCPP_HIDE_FROM_ABI _LIBCPP_AVAILABILITY_SYNC
void
atomic_flag_wait_explicit(const volatile atomic_flag* __o,
                          bool __v, memory_order __m) noexcept
{
    __o->wait(__v, __m);
}

inline _LIBCPP_HIDE_FROM_ABI _LIBCPP_AVAILABILITY_SYNC
void
atomic_flag_wait_explicit(const atomic_flag* __o,
                          bool __v, memory_order __m) noexcept
{
    __o->wait(__v, __m);
}

inline _LIBCPP_HIDE_FROM_ABI _LIBCPP_AVAILABILITY_SYNC
void
atomic_flag_notify_one(volatile atomic_flag* __o) noexcept
{
    __o->notify_one();
}

inline _LIBCPP_HIDE_FROM_ABI _LIBCPP_AVAILABILITY_SYNC
void
atomic_flag_notify_one(atomic_flag* __o) noexcept
{
    __o->notify_one();
}

inline _LIBCPP_HIDE_FROM_ABI _LIBCPP_AVAILABILITY_SYNC
void
atomic_flag_notify_all(volatile atomic_flag* __o) noexcept
{
    __o->notify_all();
}

inline _LIBCPP_HIDE_FROM_ABI _LIBCPP_AVAILABILITY_SYNC
void
atomic_flag_notify_all(atomic_flag* __o) noexcept
{
    __o->notify_all();
}

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___ATOMIC_ATOMIC_FLAG_H
