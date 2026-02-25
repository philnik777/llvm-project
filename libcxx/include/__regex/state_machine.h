//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___REGEX_STATE_MACHINE_H
#define _LIBCPP___REGEX_STATE_MACHINE_H

#include <__algorithm/equal.h>
#include <__algorithm/min.h>
#include <__algorithm/transform.h>
#include <__config>
#include <__iterator/back_insert_iterator.h>
#include <__regex/regex_error.h>
#include <__utility/pair.h>
#include <__utility/to_underlying.h>
#include <__vector/vector.h>
#include <string_view>

_LIBCPP_BEGIN_NAMESPACE_STD

template <class _CharT>
class __node;

template <class _BidirectionalIterator>
class sub_match;

template <class _BidirectionalIterator, class _Allocator = allocator<sub_match<_BidirectionalIterator> > >
class match_results;

template <class _CharT>
struct __state {
  enum __states {
    __end_state = -1000,
    __consume_input,          // -999
    __begin_marked_expr,      // -998
    __end_marked_expr,        // -997
    __pop_state,              // -996
    __accept_and_consume,     // -995
    __accept_but_not_consume, // -994
    __reject,                 // -993
    __split,
    __repeat
  };

  int __do_;
  const _CharT* __first_;
  const _CharT* __current_;
  const _CharT* __last_;
  vector<sub_match<const _CharT*> > __sub_matches_;
  vector<pair<size_t, const _CharT*> > __loop_data_;
  const __node<_CharT>* __node_;
  regex_constants::match_flag_type __flags_;
  bool __at_first_;

  _LIBCPP_HIDE_FROM_ABI __state()
      : __do_(0),
        __first_(nullptr),
        __current_(nullptr),
        __last_(nullptr),
        __node_(nullptr),
        __flags_(),
        __at_first_(false) {}
};

namespace __regex {
enum class __state : uint8_t {
  __start_anchor,
  __end_anchor,
  __positive_lookahead_start,
  __negative_lookahead_start,
  __lookahead_end,
  __match_alternative,
  __match_word_boundary,
  __match_no_word_boundary,
  __match_any,
  __match_char,
  __match_icase_char,
  __match_backref,
  __match_icase_backref,
  __match_digits,
  __match_no_digits,
  __match_whitespace,
  __match_no_whitespace,
  __match_word_character,
  __match_no_word_character,
  __match_character_list,
  __match_no_character_list,
  __marked_subexpression_begin,
  __marked_subexpression_end,
  __match_greedy_inf_repeat,
  __match_n_to_m_times,
  __match_n_times,
  __end_state,
};

template <class _CharT>
union __machine_info {
  __machine_info(__state __st) : __state_(__st) {}
  __machine_info(_CharT __c) : __char_(__c) {}
  __machine_info(uint8_t __int) : __int_(__int) {}

  template <class _Tp>
  __machine_info(_Tp) = delete;

  __state __state_;
  _CharT __char_;
  uint8_t __int_;
};

template <class _Container>
void __write_uleb(_Container& __machine, size_t __val) {
  do {
    uint8_t __byte = __val & 0x7f;
    __val >>= 7;
    if (__val)
      __byte |= 0x80;
    __machine.push_back(__byte);
  } while (__val);
}

template <class _CharT, class _Container>
void __write_string(_Container& __machine, basic_string_view<_CharT> __val) {
  __regex::__write_uleb(__machine, __val.size());
  __machine.append_range(__val);
}

template <class _CharT>
inline size_t __read_uleb(const vector<__machine_info<_CharT>>& __machine, size_t& __current_pos) {
  size_t __result = 0;
  size_t __shift  = 0;

  uint8_t __byte;
  do {
    __byte = __machine[__current_pos++].__int_;
    __result |= (__byte & 0x7f) << __shift;
    __shift += 7;
  } while (__byte & 0x80);
  return __result;
}

template <class _CharT, class _Traits>
class __state_machine {
  vector<__machine_info<_CharT>> __machine_;
  _Traits __traits_;

  struct __execution_state {
    const __state_machine* __machine_;
    vector<sub_match<const _CharT*>> __sub_matches_;
    const _CharT* __current_;
    bool __at_first_;

    bool __execute(const _CharT* __first, const _CharT* __last, size_t __current_pos = 0) {
      while (true) {
        auto __state = __machine_->__machine_[__current_pos++].__state_;
        switch (__state) {
          using enum __state;

        case __start_anchor: {
          if (!__at_first_ || __first != __current_)
            return false;
        } break;

        case __end_anchor: {
          if (__current_ != __last)
            return false;
        } break;

        case __end_state:
          return true;

        case __match_any: {
          if (__current_ == __last)
            return false;
          ++__current_;
        } break;

        case __match_char: {
          if (__current_ == __last || *__current_ != __machine_->__machine_[__current_pos++].__char_)
            return false;
          ++__current_;
        } break;

        case __match_icase_char: {
          if (__current_ == __last ||
              __machine_->__traits_.translate_nocase(*__current_) != __machine_->__machine_[__current_pos++].__char_)
            return false;
          ++__current_;
        } break;

        case __match_alternative: {
          auto __offset = __regex::__read_uleb(__machine_->__machine_, __current_pos);
          __execution_state __tmp_exec_state = *this;
          if (__tmp_exec_state.__execute(__first, __last, __current_pos + __offset)) {
            *this = std::move(__tmp_exec_state);
            return true;
          }

          return __execute(__first, __last, __current_pos);
        } break;

        case __match_n_to_m_times: {
          auto __min         = __regex::__read_uleb(__machine_->__machine_, __current_pos);
          auto __range       = __regex::__read_uleb(__machine_->__machine_, __current_pos);
          auto __jump_offset = __regex::__read_uleb(__machine_->__machine_, __current_pos);

          for (size_t __i = 0; __i != __min; ++__i) {
            if (!__execute(__first, __last, __current_pos))
              return false;
          }

          bool __found_best_match = false;
          __execution_state __best_exec_state;
          for (size_t __i = 0; __i != __range + 1; ++__i) {
            __execution_state __tmp_exec_state = *this;
            if (__tmp_exec_state.__execute(__first, __last, __current_pos + __jump_offset)) {
              __found_best_match = true;
              __best_exec_state = std::move(__tmp_exec_state);
            }

            __tmp_exec_state = *this;
            if (!__tmp_exec_state.__execute(__first, __last, __current_pos))
              break;

            if (__tmp_exec_state.__current_ == __current_) {
              *this = std::move(__tmp_exec_state);
              if (__execute(__first, __last, __current_pos + __jump_offset))
                return true;
              break;
            }

            *this = std::move(__tmp_exec_state);
          }
          *this = std::move(__best_exec_state);
          return __found_best_match;
        } break;

        case __match_greedy_inf_repeat: {
          auto __jump_offset      = __regex::__read_uleb(__machine_->__machine_, __current_pos);
          bool __found_best_match = false;
          __execution_state __best_exec_state;
          while (true) {
            __execution_state __tmp_exec_state = *this;
            if (__tmp_exec_state.__execute(__first, __last, __current_pos + __jump_offset)) {
              __found_best_match = true;
              __best_exec_state  = std::move(__tmp_exec_state);
            }

            __tmp_exec_state = *this;
            if (!__tmp_exec_state.__execute(__first, __last, __current_pos))
              break;

            if (__tmp_exec_state.__current_ == __current_) {
              *this = std::move(__tmp_exec_state);
              if (__execute(__first, __last, __current_pos + __jump_offset))
                return true;
              break;
            }

            *this = std::move(__tmp_exec_state);
          }
          *this = std::move(__best_exec_state);
          return __found_best_match;
        } break;

        case __match_backref: {
          sub_match<const _CharT*>& __match =
              __sub_matches_[__regex::__read_uleb(__machine_->__machine_, __current_pos) - 1];
          if (!__match.matched)
            return false;

          auto __len = __match.second - __match.first;
          if (__last - __current_ < __len || !std::equal(__match.first, __match.second, __current_))
            return false;

          __current_ += __len;
        } break;

        case __match_icase_backref: {
          sub_match<const _CharT*>& __match =
              __sub_matches_[__regex::__read_uleb(__machine_->__machine_, __current_pos) - 1];
          if (!__match.matched)
            return false;

          auto __len = __match.second - __match.first;
          if (__last - __current_ < __len)
            return false;

          for (ptrdiff_t __i = 0; __i != __len; ++__i) {
            if (__machine_->__traits_.translate_nocase(__match.first[__i]) !=
                __machine_->__traits_.translate_nocase(__current_[__i]))
              return false;
          }

          __current_ += __len;
        } break;

        case __match_character_list:
        case __match_no_character_list: {
          if (__current_ == __last)
            return false;
          constexpr auto __buffer_size =
              std::max(sizeof(typename _Traits::char_class_type) / sizeof(_CharT), size_t(1));
          _CharT __buffer[__buffer_size];
          for (size_t __i = 0; __i != __buffer_size; ++__i)
            __buffer[__i] = __machine_->__machine_[__current_pos++].__char_;
          typename _Traits::char_class_type __mask;
          __builtin_memcpy(&__mask, __buffer, sizeof(typename _Traits::char_class_type));

          auto __chars       = __regex::__read_uleb(__machine_->__machine_, __current_pos);
          auto __digraphs    = __regex::__read_uleb(__machine_->__machine_, __current_pos) * 2;
          auto __ranges      = __regex::__read_uleb(__machine_->__machine_, __current_pos) * 4;
          auto __equiv_count = __regex::__read_uleb(__machine_->__machine_, __current_pos);
          auto __equiv_size  = __regex::__read_uleb(__machine_->__machine_, __current_pos);

          bool __found = false;

          for (size_t __i = 0; __i != __chars; ++__i) {
            if (__machine_->__machine_[__current_pos + __i].__char_ == *__current_) {
              __found = true;
              break;
            }
          }

          __current_pos += __chars;

          if (__found) {
            __current_pos += __digraphs + __ranges + __equiv_size;
            ++__current_;
            if (__state == __match_no_character_list)
              return false;
            break;
          }

          if (__current_ + 1 != __last) {
            _CharT __vals[2] = {__current_[0], __current_[1]};

            for (size_t __i = 0; __i != __digraphs; __i += 2) {
              if (__machine_->__machine_[__current_pos + __i].__char_ == __vals[0] &&
                  __machine_->__machine_[__current_pos + __i + 1].__char_ == __vals[1]) {
                __found = true;
                break;
              }
            }
          }

          __current_pos += __digraphs;

          if (__found) {
            __current_pos += __ranges + __equiv_size;
            __current_ += 2;
            if (__state == __match_no_character_list)
              return false;
            break;
          }

          auto __cmp = __machine_->__traits_.transform(__current_, __current_ + 1);
          for (size_t __i = 0; __i != __ranges; __i += 4) {
            _CharT __range_info[4];
            std::transform(__machine_->__machine_.begin() + __current_pos + __i,
                           __machine_->__machine_.begin() + __current_pos + __i + 4,
                           __range_info,
                           [](__machine_info<_CharT> __val) { return __val.__char_; });
            basic_string_view<_CharT> __min(__range_info, __range_info[1] == '\0' ? 1 : 2);
            basic_string_view<_CharT> __max(__range_info + 2, __range_info[3] == '\0' ? 1 : 2);
            if (__min <= __cmp && __cmp <= __max) {
              __found = true;
              __current_ += __cmp.size();
              break;
            }
          }

          __current_pos += __ranges;

          if (__found) {
            __current_pos += __equiv_size;
            if (__state == __match_no_character_list)
              return false;
            break;
          }

          if (__machine_->__traits_.isctype(*__current_, __mask)) {
            ++__current_;
            if (__state == __match_no_character_list)
              return false;
            break;
          }

          auto __after_pos   = __current_pos + __equiv_size;
          auto __transformed = __machine_->__traits_.transform_primary(__current_, __current_ + 1);
          for (size_t __i = 0; __i != __equiv_count; ++__i) {
            auto __size = __regex::__read_uleb(__machine_->__machine_, __current_pos);
            basic_string<_CharT> __str;
            std::transform(__machine_->__machine_.begin() + __current_pos,
                           __machine_->__machine_.begin() + __current_pos + __size,
                           std::back_inserter(__str),
                           [](__machine_info<_CharT> __v) { return __v.__char_; });
            __current_pos += __size;
            if (__transformed == __str) {
              __found = true;
              break;
            }
          }

          __current_pos = __after_pos;

          if (__found) {
            ++__current_;
            if (__state == __match_no_character_list)
              return false;
            break;
          }

          if (__state == __match_no_character_list) {
            ++__current_;
            break;
          }
          return false;

        } break;

        case __marked_subexpression_begin: {
          auto __match                  = __regex::__read_uleb(__machine_->__machine_, __current_pos);
          __sub_matches_[__match].first = __current_;
        } break;

        case __marked_subexpression_end: {
          auto __match                    = __regex::__read_uleb(__machine_->__machine_, __current_pos);
          __sub_matches_[__match].second  = __current_;
          __sub_matches_[__match].matched = true;
        } break;

        default:
          ::std::__libcpp_verbose_abort(
              "Not yet implemented: %hhu\n", std::to_underlying(__machine_->__machine_[__current_pos - 1].__state_));
        }
      }
    }
  };

public:
  __state_machine(_Traits __traits) : __traits_(__traits) {}

  void push_back(__machine_info<_CharT> __info) { __machine_.push_back(__info); }

  void __push_char_matcher(_CharT __char) {
    push_back(__state::__match_char);
    push_back(__char);
  }

  void __push_icase_char_matcher(_CharT __char) {
    push_back(__state::__match_icase_char);
    push_back(__traits_.translate_nocase(__char));
  }

  void __push_backref_matcher(size_t __ref) {
    push_back(__state::__match_backref);
    __regex::__write_uleb(*this, __ref);
  }

  void __push_icase_backref_matcher(size_t __ref) {
    push_back(__state::__match_icase_backref);
    __regex::__write_uleb(*this, __ref);
  }

  template <class _Range>
  void append_range(_Range&& __range) {
    __machine_.append_range(__range);
  }

  void insert(size_t __offset, vector<__machine_info<_CharT>>& __info) {
    __machine_.insert(__machine_.begin() + __offset, __info.begin(), __info.end());
  }

  size_t size() const { return __machine_.size(); }

  __execution_state
  __get_exec_state(vector<sub_match<const _CharT*>>& __sub_matches, const _CharT* __current, bool __at_first) const {
    return __execution_state{this, __sub_matches, __current, __at_first};
  }

  _Traits __get_traits() { return __traits_; }
};

template <class _CharT, class _Traits>
struct __bracket_expr {
  vector<_CharT> __chars_;
  vector<_CharT> __digraphs_;
  vector<_CharT> __ranges_;
  vector<typename _Traits::string_type> __equivalences_;
  typename _Traits::char_class_type __mask_ = 0;

  void __write_to_machine(__state_machine<_CharT, _Traits>& __machine) {
    _CharT __buffer[std::max(sizeof(typename _Traits::char_class_type) / sizeof(_CharT), size_t(1))];
    __builtin_memcpy(__buffer, &__mask_, sizeof(__buffer));
    __machine.append_range(__buffer);

    basic_string<_CharT> __equivalences_buffer;
    for (auto& __eq : __equivalences_)
      __regex::__write_string<_CharT>(__equivalences_buffer, __eq);
    __regex::__write_uleb(__machine, __chars_.size());
    __regex::__write_uleb(__machine, __digraphs_.size() / 2);
    __regex::__write_uleb(__machine, __ranges_.size() / 4);
    __regex::__write_uleb(__machine, __equivalences_.size());
    __regex::__write_uleb(__machine, __equivalences_buffer.size());
    __machine.append_range(__chars_);
    __machine.append_range(__digraphs_);
    __machine.append_range(__ranges_);
    __machine.append_range(__equivalences_buffer);
  }
};
} // namespace __regex

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___REGEX_STATE_MACHINE_H
