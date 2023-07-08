// -*- C++ -*-
//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___MEMORY_POINTER_TRAITS_H
#define _LIBCPP___MEMORY_POINTER_TRAITS_H

#include <__config>
#include <__memory/addressof.h>
#include <__type_traits/conditional.h>
#include <__type_traits/conjunction.h>
#include <__type_traits/decay.h>
#include <__type_traits/is_class.h>
#include <__type_traits/is_function.h>
#include <__type_traits/is_void.h>
#include <__type_traits/void_t.h>
#include <__utility/declval.h>
#include <cstddef>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

template <class _Tp, class = void>
struct __has_element_type : false_type {};

template <class _Tp>
struct __has_element_type<_Tp, __void_t<typename _Tp::element_type> > : true_type {};

template <class _Ptr, bool = __has_element_type<_Ptr>::value>
struct __pointer_traits_element_type;

template <class _Ptr>
struct __pointer_traits_element_type<_Ptr, true>
{
    typedef _LIBCPP_NODEBUG typename _Ptr::element_type type;
};

template <template <class, class...> class _Sp, class _Tp, class ..._Args>
struct __pointer_traits_element_type<_Sp<_Tp, _Args...>, true>
{
    typedef _LIBCPP_NODEBUG typename _Sp<_Tp, _Args...>::element_type type;
};

template <template <class, class...> class _Sp, class _Tp, class ..._Args>
struct __pointer_traits_element_type<_Sp<_Tp, _Args...>, false>
{
    typedef _LIBCPP_NODEBUG _Tp type;
};

template <class _Tp, class = void>
struct __has_difference_type : false_type {};

template <class _Tp>
struct __has_difference_type<_Tp, __void_t<typename _Tp::difference_type> > : true_type {};

template <class _Ptr, bool = __has_difference_type<_Ptr>::value>
struct __pointer_traits_difference_type
{
    typedef _LIBCPP_NODEBUG ptrdiff_t type;
};

template <class _Ptr>
struct __pointer_traits_difference_type<_Ptr, true>
{
    typedef _LIBCPP_NODEBUG typename _Ptr::difference_type type;
};

template <class _Tp, class _Up>
struct __has_rebind
{
private:
    template <class _Xp> static false_type __test(...);
    _LIBCPP_SUPPRESS_DEPRECATED_PUSH
    template <class _Xp> static true_type __test(typename _Xp::template rebind<_Up>* = 0);
    _LIBCPP_SUPPRESS_DEPRECATED_POP
public:
    static const bool value = decltype(__test<_Tp>(0))::value;
};

template <class _Tp, class _Up, bool = __has_rebind<_Tp, _Up>::value>
struct __pointer_traits_rebind
{
    typedef _LIBCPP_NODEBUG typename _Tp::template rebind<_Up> type;
};

template <template <class, class...> class _Sp, class _Tp, class ..._Args, class _Up>
struct __pointer_traits_rebind<_Sp<_Tp, _Args...>, _Up, true>
{
    typedef _LIBCPP_NODEBUG typename _Sp<_Tp, _Args...>::template rebind<_Up> type;
};

template <template <class, class...> class _Sp, class _Tp, class ..._Args, class _Up>
struct __pointer_traits_rebind<_Sp<_Tp, _Args...>, _Up, false>
{
    typedef _Sp<_Up, _Args...> type;
};

template <class _Ptr>
struct _LIBCPP_TEMPLATE_VIS pointer_traits
{
    typedef _Ptr                                                     pointer;
    typedef typename __pointer_traits_element_type<pointer>::type    element_type;
    typedef typename __pointer_traits_difference_type<pointer>::type difference_type;

    template <class _Up> using rebind = typename __pointer_traits_rebind<pointer, _Up>::type;

private:
    struct __nat {};
public:
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX20
    static pointer pointer_to(__conditional_t<is_void<element_type>::value, __nat, element_type>& __r)
        {return pointer::pointer_to(__r);}
};

template <class _Tp>
struct _LIBCPP_TEMPLATE_VIS pointer_traits<_Tp*>
{
    typedef _Tp*      pointer;
    typedef _Tp       element_type;
    typedef ptrdiff_t difference_type;

    template <class _Up> using rebind = _Up*;

private:
    struct __nat {};
public:
    _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_SINCE_CXX20
    static pointer pointer_to(__conditional_t<is_void<element_type>::value, __nat, element_type>& __r) noexcept
        {return _VSTD::addressof(__r);}
};

template <class _From, class _To>
using __rebind_pointer_t = typename pointer_traits<_From>::template rebind<_To>;

// to_address

template <class _Pointer, class = void>
struct __to_address_helper;

template <class _Tp>
_LIBCPP_INLINE_VISIBILITY constexpr
_Tp* __to_address(_Tp* __p) noexcept {
    static_assert(!is_function<_Tp>::value, "_Tp is a function type");
    return __p;
}

template <class _Pointer, class = void>
struct _HasToAddress : false_type {};

template <class _Pointer>
struct _HasToAddress<_Pointer,
    decltype((void)pointer_traits<_Pointer>::to_address(std::declval<const _Pointer&>()))
> : true_type {};

template <class _Pointer, class = void>
struct _HasArrow : false_type {};

template <class _Pointer>
struct _HasArrow<_Pointer,
    decltype((void)std::declval<const _Pointer&>().operator->())
> : true_type {};

template <class _Pointer>
struct _IsFancyPointer {
  static const bool value = _HasArrow<_Pointer>::value || _HasToAddress<_Pointer>::value;
};

// enable_if is needed here to avoid instantiating checks for fancy pointers on raw pointers
template <class _Pointer, class = __enable_if_t<
    _And<is_class<_Pointer>, _IsFancyPointer<_Pointer> >::value
> >
_LIBCPP_INLINE_VISIBILITY constexpr
__decay_t<decltype(__to_address_helper<_Pointer>::__call(std::declval<const _Pointer&>()))>
__to_address(const _Pointer& __p) noexcept {
    return __to_address_helper<_Pointer>::__call(__p);
}

template <class _Pointer, class>
struct __to_address_helper {
    _LIBCPP_INLINE_VISIBILITY constexpr
    static decltype(_VSTD::__to_address(std::declval<const _Pointer&>().operator->()))
    __call(const _Pointer& __p) noexcept {
        return _VSTD::__to_address(__p.operator->());
    }
};

template <class _Pointer>
struct __to_address_helper<_Pointer, decltype((void)pointer_traits<_Pointer>::to_address(std::declval<const _Pointer&>()))> {
    _LIBCPP_INLINE_VISIBILITY constexpr
    static decltype(pointer_traits<_Pointer>::to_address(std::declval<const _Pointer&>()))
    __call(const _Pointer& __p) noexcept {
        return pointer_traits<_Pointer>::to_address(__p);
    }
};

#if _LIBCPP_STD_VER >= 20
template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY constexpr
auto to_address(_Tp *__p) noexcept {
    return _VSTD::__to_address(__p);
}

template <class _Pointer>
inline _LIBCPP_INLINE_VISIBILITY constexpr
auto to_address(const _Pointer& __p) noexcept -> decltype(std::__to_address(__p)) {
    return _VSTD::__to_address(__p);
}
#endif

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___MEMORY_POINTER_TRAITS_H
