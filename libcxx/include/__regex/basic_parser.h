//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___REGEX_ECMA_PARSER_H
#define _LIBCPP___REGEX_ECMA_PARSER_H

#include <__algorithm/search.h>
#include <__config>
#include <__iterator/next.h>
#include <__regex/regex_error.h>
#include <__regex/state_machine.h>
#include <__utility/exchange.h>
#include <string>

#define _LIBCPP_PARSER_FUNCTION
#define _LIBCPP_MUST_TAIL [[clang::musttail]]

_LIBCPP_BEGIN_NAMESPACE_STD

namespace __regex::__basic::inline __preserve_none {

template <class _CharT, class _Traits, class _ForwardIterator>
_LIBCPP_PARSER_FUNCTION bool
__parse_something(__state_machine<_CharT, _Traits>& __machine, _ForwardIterator& __first, _ForwardIterator __last) {}

template <class _CharT, class _Traits, class _ForwardIterator>
_LIBCPP_PARSER_FUNCTION bool
__parse_quoted_char(__state_machine<_CharT, _Traits>& __machine, _ForwardIterator& __first, _ForwardIterator __last) {
  _LIBCPP_ASSERT_INTERNAL(__first != __last, "Expected parseable character");
  auto __next = std::next(__first);
  if (__next == __last)
    return false;
  if (*__first != '\\')
    return false;
  switch (*__next) {
  case '^':
  case '.':
  case '*':
  case '[':
  case '$':
  case '\\':
    __machine.__push_char_matcher(*__next);
    __first = ++__next;
    return true;
  default:
    return false;
  }
}

template <class _CharT, class _Traits, class _ForwardIterator>
_LIBCPP_PARSER_FUNCTION bool __parse_back_open_paren(
    __state_machine<_CharT, _Traits>& __machine, _ForwardIterator& __first, _ForwardIterator __last) {
  if (__first == __last)
    return false;
  auto __next = std::next(__first);
  if (__next == __last)
    return false;
  if (*__first != '\\' || *__next != '(')
    return false;
  __first = ++__next;
  return true;
}

template <class _CharT, class _Traits, class _ForwardIterator>
_LIBCPP_PARSER_FUNCTION bool __parse_back_close_paren(
    __state_machine<_CharT, _Traits>& __machine, _ForwardIterator& __first, _ForwardIterator __last) {
  if (__first == __last)
    return false;
  auto __next = std::next(__first);
  if (__next == __last)
    return false;
  if (*__first != '\\' || *__next != ')')
    return false;
  __first = ++__next;
  return true;
}

template <class _CharT, class _Traits, class _ForwardIterator>
_LIBCPP_PARSER_FUNCTION bool __parse_back_open_brace(
    __state_machine<_CharT, _Traits>& __machine, _ForwardIterator& __first, _ForwardIterator __last) {
  if (__first == __last)
    return false;
  auto __next = std::next(__first);
  if (__next == __last)
    return false;
  if (*__first != '\\' || *__next != '{')
    return false;
  __first = ++__next;
  return true;
}

template <class _CharT, class _Traits, class _ForwardIterator>
class __parser {
  __state_machine<_CharT, _Traits> __machine_;
  size_t __marked_count_ = 0;
  _ForwardIterator __first_;
  _ForwardIterator __last_;
  regex_constants::syntax_option_type __flags_;

  _LIBCPP_PARSER_FUNCTION void __push_char_matcher(_CharT __char) {
    if (__flags_ & regex_constants::icase)
      __machine_.__push_icase_char_matcher(__char);
    else
      __machine_.__push_char_matcher(__char);
  }

  _LIBCPP_PARSER_FUNCTION void __push_backref_matcher(size_t __ref) {
    if (__flags_ & regex_constants::icase)
      __machine_.__push_icase_backref_matcher(__ref);
    else
      __machine_.__push_backref_matcher(__ref);
  }

  _LIBCPP_PARSER_FUNCTION bool __parse_back_close_brace() {
    if (__first_ == __last_)
      return false;
    auto __next = std::next(__first_);
    if (__next == __last_)
      return false;
    if (*__first_ != '\\' || *__next != '}')
      return false;
    __first_ = ++__next;
    return true;
  }

  _LIBCPP_PARSER_FUNCTION bool __parse_ord_char(_ForwardIterator& __first, _ForwardIterator __last) {
    _LIBCPP_ASSERT_INTERNAL(__first != __last, "Expected parseable character");
    auto __next = std::next(__first);
    if (__next == __last && *__first == '$')
      return false;
    if (*__first == '.' || *__first == '\\' || *__first == '[')
      return false;
    __push_char_matcher(*__first);
    __first = __next;
    return true;
  }

  _LIBCPP_PARSER_FUNCTION bool __parse_equivalence_class(__bracket_expr<_CharT, _Traits>& __buffer) {
    char __equal_close[2]   = {'=', ']'};
    auto __closing_sequence = std::search(__first_, __last_, __equal_close, __equal_close + 2);

    if (__closing_sequence == __last_)
      std::__throw_regex_error<regex_constants::error_brack>();

    auto __collate_name = __machine_.__get_traits().lookup_collatename(__first_, __closing_sequence);
    if (__collate_name.empty())
      std::__throw_regex_error<regex_constants::error_collate>();

    auto __equiv_name = __machine_.__get_traits().transform_primary(__collate_name.begin(), __collate_name.end());
    if (!__equiv_name.empty()) {
      __buffer.__equivalences_.push_back(std::move(__equiv_name));
      __first_ = std::next(__closing_sequence, 2);
      return true;
    }

    switch (__collate_name.size()) {
    case 1:
      __buffer.__chars_.push_back(__collate_name[0]);
      break;
    case 2:
      __buffer.__digraphs_.push_back(__collate_name[0]);
      __buffer.__digraphs_.push_back(__collate_name[1]);
      break;
    default:
      std::__throw_regex_error<regex_constants::error_collate>();
    }
    __first_ = std::next(__closing_sequence, 2);
    return true;
  }

  _LIBCPP_PARSER_FUNCTION bool __parse_character_class(__bracket_expr<_CharT, _Traits>& __machine) {
    char __equal_close[2]   = {':', ']'};
    auto __closing_sequence = std::search(__first_, __last_, __equal_close, __equal_close + 2);

    if (__closing_sequence == __last_)
      std::__throw_regex_error<regex_constants::error_brack>();

    auto __class_type =
        __machine_.__get_traits().lookup_classname(__first_, __closing_sequence, __flags_ & regex_constants::icase);

    if (__class_type == 0)
      std::__throw_regex_error<regex_constants::error_ctype>();

    __machine.__mask_ |= __class_type;
    __first_ = std::next(__closing_sequence, 2);

    return true;
  }

  _LIBCPP_PARSER_FUNCTION void __parse_collating_symbol(basic_string<_CharT>& __buffer) {
    char __equal_close[2]   = {'.', ']'};
    auto __closing_sequence = std::search(__first_, __last_, __equal_close, __equal_close + 2);

    if (__closing_sequence == __last_)
      std::__throw_regex_error<regex_constants::error_brack>();

    __buffer = __machine_.__get_traits().lookup_collatename(__first_, __closing_sequence);
    switch (__buffer.size()) {
    case 1:
    case 2:
      break;
    default:
      std::__throw_regex_error<regex_constants::error_collate>();
    }

    __first_ = std::next(__closing_sequence, 2);
  }

  _LIBCPP_PARSER_FUNCTION bool __parse_expression_term(__bracket_expr<_CharT, _Traits>& __buffer) {
    _LIBCPP_ASSERT_INTERNAL(__first_ != __last_, "Expected parseable character");

    if (*__first_ == ']')
      return false;
    auto __next = std::next(__first_);
    if (__next == __last_)
      return false;

    if (*__first_ == '[') {
      if (*__next == '=') {
        __first_ = ++__next;
        _LIBCPP_MUST_TAIL return __parse_equivalence_class(__buffer);
      }

      if (*__next == ':') {
        __first_ = ++__next;
        _LIBCPP_MUST_TAIL return __parse_character_class(__buffer);
      }
    }

    basic_string<_CharT> __start_range;
    if (*__first_ == '[' && *__next == '.') {
      __first_ = ++__next;
      __parse_collating_symbol(__start_range);
    } else {
      __start_range = *__first_;
      ++__first_;
    }

    if (__first_ == __last_)
      return false;

    if (*__first_ == ']') {
      if (__start_range.size() == 1) {
        __buffer.__chars_.push_back(__start_range[0]);
      } else {
        _LIBCPP_ASSERT_INTERNAL(__start_range.size() == 2, "Unexpected range");
        __buffer.__digraphs_.append_range(__start_range);
      }
      return true;
    }

    __next = std::next(__first_);
    if (__next == __last_)
      return false;

    if (*__first_ != '-' || *__next == ']') {
      if (__start_range.size() == 1) {
        __buffer.__chars_.push_back(__start_range[0]);
      } else {
        _LIBCPP_ASSERT_INTERNAL(__start_range.size() == 2, "Unexpected range");
        __buffer.__digraphs_.append_range(__start_range);
      }
      return true;
    }

    basic_string<_CharT> __end_range;
    __first_ = __next;
    ++__next;
    if (__next == __last_)
      return false;
    if (*__first_ == '[' && *__next == '.') {
      __first_ = ++__next;
      __parse_collating_symbol(__end_range);
    } else {
      __end_range = *__first_;
      ++__first_;
    }
    __buffer.__ranges_.push_back(__start_range[0]);
    __buffer.__ranges_.push_back(__start_range.size() == 2 ? __start_range[1] : '\0');
    __buffer.__ranges_.push_back(__end_range[0]);
    __buffer.__ranges_.push_back(__end_range.size() == 2 ? __end_range[1] : '\0');

    return true;
  }

  _LIBCPP_PARSER_FUNCTION void __parse_follow_list(__bracket_expr<_CharT, _Traits>& __buffer) {
    _LIBCPP_ASSERT_INTERNAL(__first_ != __last_, "Expected parseable character");

    while (__parse_expression_term(__buffer))
      ;
  }

  _LIBCPP_PARSER_FUNCTION bool __parse_bracket_expression() {
    _LIBCPP_ASSERT_INTERNAL(__first_ != __last_, "Expected parseable character");
    if (*__first_ != '[')
      return false;
    ++__first_;
    if (__first_ == __last_)
      std::__throw_regex_error<regex_constants::error_brack>();
    if (*__first_ == '^') {
      ++__first_;
      if (__first_ == __last_)
        std::__throw_regex_error<regex_constants::error_brack>();

      __machine_.push_back(__state::__match_no_character_list);
    } else {
      __machine_.push_back(__state::__match_character_list);
    }
    __bracket_expr<_CharT, _Traits> __buffer;

    if (*__first_ == ']') {
      __buffer.__chars_.push_back(']');
      ++__first_;
      if (__first_ == __last_)
        std::__throw_regex_error<regex_constants::error_brack>();
    }

    __parse_follow_list(__buffer);
    if (__first_ == __last_)
      std::__throw_regex_error<regex_constants::error_brack>();
    if (*__first_ == '-') {
      __buffer.__chars_.push_back('-');
      ++__first_;
    }
    if (__first_ == __last_ || *__first_ != ']')
      std::__throw_regex_error<regex_constants::error_brack>();
    ++__first_;
    __buffer.__write_to_machine(__machine_);
    return true;
  }

  _LIBCPP_PARSER_FUNCTION bool __parse_one_char_or_coll_elem() {
    if (__first_ == __last_)
      return false;

    if (__parse_ord_char(__first_, __last_))
      return true;
    if (__basic::__parse_quoted_char(__machine_, __first_, __last_))
      return true;

    if (*__first_ == '.') {
      __machine_.push_back(__state::__match_any);
      ++__first_;
      return true;
    } else {
      return __parse_bracket_expression();
    }
  }

  _LIBCPP_PARSER_FUNCTION bool __parse_backref() {
    if (__first_ == __last_)
      return false;

    auto __next = std::next(__first_);
    if (__next == __last_)
      return false;
    if (*__first_ != '\\' || *__next < '0' || *__next > '9')
      return false;
    if (*__next == '0') {
      __push_char_matcher('\0');
      __first_ = ++__next;
      return true;
    }
    auto __val = *__next - '0';
    if (__val > __marked_count_)
      std::__throw_regex_error<regex_constants::error_backref>();
    __push_backref_matcher(__val);
    __first_ = ++__next;
    return true;
  }

  _LIBCPP_PARSER_FUNCTION bool __parse_nondupl() {
    if (__parse_one_char_or_coll_elem())
      return true;

    if (__basic::__parse_back_open_paren(__machine_, __first_, __last_)) {
      size_t __subexpr_num = __marked_count_++;
      __machine_.push_back(__state::__marked_subexpression_begin);
      __regex::__write_uleb(__machine_, __subexpr_num);
      __parse_re_expression();
      if (!__basic::__parse_back_close_paren(__machine_, __first_, __last_))
        std::__throw_regex_error<regex_constants::error_paren>();
      __machine_.push_back(__state::__marked_subexpression_end);
      __regex::__write_uleb(__machine_, __subexpr_num);
      return true;
    } else {
      return __parse_backref();
    }
  }

  _LIBCPP_PARSER_FUNCTION bool __parse_dup_count(size_t& __num) {
    if (__first_ == __last_ || *__first_ < '0' || *__first_ > '9')
      return false;
    __num = 0;
    for (; __first_ != __last_ && *__first_ >= '0' && *__first_ <= '9'; ++__first_) {
      if (__num >= numeric_limits<size_t>::max() / 10)
        std::__throw_regex_error<regex_constants::error_badbrace>();
      __num *= 10;
      __num += *__first_ - '0';
    }
    return true;
  }

  _LIBCPP_PARSER_FUNCTION bool __parse_dupl_symbol(size_t __expr_start) {
    if (__first_ == __last_)
      return false;

    if (*__first_ == '*') {
      vector<__machine_info<_CharT>> __buffer;
      __buffer.push_back(__state::__match_greedy_inf_repeat);
      __regex::__write_uleb(__buffer, __machine_.size() - __expr_start + 1);
      __machine_.insert(__expr_start, __buffer);
      __machine_.push_back(__state::__end_state);
      ++__first_;
      return true;
    }

    if (!__basic::__parse_back_open_brace(__machine_, __first_, __last_))
      return false;

    size_t __min;
    if (!__parse_dup_count(__min))
      std::__throw_regex_error<regex_constants::error_badbrace>();
    if (__first_ == __last_)
      std::__throw_regex_error<regex_constants::error_brace>();
    if (*__first_ == ',') {
      ++__first_;
      size_t __max;
      if (!__parse_dup_count(__max))
        __max = numeric_limits<size_t>::max();
      if (__max < __min || !__parse_back_close_brace())
        std::__throw_regex_error<regex_constants::error_badbrace>();
      vector<__machine_info<_CharT>> __buffer;
      __buffer.push_back(__state::__match_n_to_m_times);
      __regex::__write_uleb(__buffer, __min);
      __regex::__write_uleb(__buffer, __max - __min);
      __regex::__write_uleb(__buffer, __machine_.size() - __expr_start + 1);
      __machine_.insert(__expr_start, __buffer);
      __machine_.push_back(__state::__end_state);
      return true;
    }

    if (!__parse_back_close_brace())
      std::__throw_regex_error<regex_constants::error_brace>();
    __machine_.push_back(__state::__match_n_times);
    __regex::__write_uleb(__machine_, __min);
    return true;
  }

  _LIBCPP_PARSER_FUNCTION bool __parse_simple_re() {
    if (__first_ == __last_)
      return false;

    auto __expr_start = __machine_.size();
    if (__parse_nondupl()) {
      __parse_dupl_symbol(__expr_start);
      return true;
    }
    return false;
  }

  _LIBCPP_PARSER_FUNCTION void __parse_re_expression() {
    while (__parse_simple_re())
      ;
  }

public:
  __parser(
      _ForwardIterator __first, _ForwardIterator __last, _Traits __traits, regex_constants::syntax_option_type __flags)
      : __machine_(__traits), __first_(__first), __last_(__last), __flags_(__flags) {}

  void __parse_basic() {
    __scope_guard __g([&] { __machine_.push_back(__state::__end_state); });

    if (__first_ == __last_)
      return;

    if (*__first_ == '^') {
      __machine_.push_back(__state::__start_anchor);
      ++__first_;
      if (__first_ == __last_)
        return;
    }

    __parse_re_expression();

    if (__first_ != __last_) {
      auto __next = std::next(__first_);
      if (__next == __last_ && *__first_ == '$') {
        __machine_.push_back(__state::__end_anchor);
        __first_ = __next;
      }
    }

    if (__first_ != __last_)
      std::__throw_regex_error<regex_constants::__re_err_empty>();
  }

  void __parse_grep() {
    auto __newline = std::find(__first_, __last_, '\n');
    if (__newline != __first_) {
      std::swap(__last_, __newline);
      __parse_basic();
      std::swap(__last_, __newline);
      if (__first_ != __newline)
        std::__throw_regex_error<regex_constants::__re_err_grammar>();
    }
    if (__first_ != __last_)
      ++__first_;
    while (__first_ != __last_) {
      __newline = std::find(__first_, __last_, '\n');
      vector<__machine_info<_CharT>> __buffer;
      __buffer.push_back(__state::__match_alternative);
      __regex::__write_uleb(__buffer, __machine_.size());
      __machine_.insert(0, __buffer);
      std::swap(__last_, __newline);
      __parse_basic();
      std::swap(__last_, __newline);
      if (__first_ != __newline)
        std::__throw_regex_error<regex_constants::__re_err_grammar>();
      if (__first_ != __last_)
        ++__first_;
    }
  }

  __state_machine<_CharT, _Traits> __extract_machine() { return std::move(__machine_); }
  size_t mark_count() const { return __marked_count_; }
};
} // namespace __regex::__basic::inline __preserve_none

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___REGEX_ECMA_PARSER_H
