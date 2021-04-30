#include <cstring>
#include <limits>
#include <stdexcept>
#include <string>
#include <algorithm>

namespace c10 {

/**
 * Reimplementation of std::string_view for C++11.
 * Implemented following the interface definition in
 * https://en.cppreference.com/w/cpp/string/basic_string_view
 * See there for the API documentation.
 *
 * Difference: We don't have a Traits template parameter because
 * std::char_traits isn't constexpr and we'd have to reimplement
 * std::char_traits if we wanted to use it with our constexpr basic_string_view.
 */
template <class CharT>
class basic_string_view final {
 public:
  using value_type = CharT;
  using pointer = CharT*;
  using const_pointer = const CharT*;
  using reference = CharT&;
  using const_reference = const CharT&;
  using const_iterator = const CharT*;
  using iterator = const_iterator;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  static constexpr size_type npos = size_type(-1);

  constexpr basic_string_view() noexcept : begin_(nullptr), size_(0) {}

  explicit constexpr basic_string_view(const_pointer str, size_type count)
      : begin_(str), size_(count) {}

  /* implicit */ constexpr basic_string_view(const_pointer str)
      : basic_string_view(str, strlen_(str)) {}

  /* implicit */ basic_string_view(const ::std::basic_string<CharT>& str)
      : basic_string_view(str.data(), str.size()) {}

  constexpr basic_string_view(const basic_string_view&) noexcept = default;

  constexpr const_pointer data() const noexcept {
    return begin_;
  }

  constexpr size_type size() const noexcept {
    return size_;
  }

  constexpr size_type find(basic_string_view v, size_type pos = 0) const
      noexcept {
#if __cpp_constexpr >= 201304
    // if we are in C++14, write it iteratively. This is faster.
    if (v.size() == 0) {
      return pos <= size() ? pos : npos;
    }

    if (pos + v.size() <= size()) {
      for (size_type cur = pos, end = size() - v.size(); cur <= end; ++cur) {
        if (v.at_(0) == at_(cur) &&
            v.substr_(1).equals_(substr_(cur + 1, v.size() - 1))) {
          return cur;
        }
      }
    }
    return npos;
#else
    // if we are in C++11, we need to do it recursively because of constexpr
    // restrictions.
    return (v.size() == 0) ? (pos <= size() ? pos : npos)
                           : (pos + v.size() > size())
            ? npos
            : (v.at_(0) == at_(pos) &&
               v.substr_(1).equals_(substr_(pos + 1, v.size() - 1)))
                ? pos
                : find(v, pos + 1);
#endif
  }

  constexpr size_type find(const_pointer s, size_type pos, size_type count)
      const {
    return find(basic_string_view(s, count), pos);
  }

  constexpr size_type find(const_pointer s, size_type pos = 0) const {
    return find(basic_string_view(s), pos);
  }

  static constexpr size_type strlen_(const_pointer str) noexcept {
#if __cpp_constexpr >= 201304
    // if we are in C++14, write it iteratively. This is faster.
    const_pointer current = str;
    while (*current != '\0') {
      ++current;
    }
    return current - str;
#else
    // if we are in C++11, we need to do it recursively because of constexpr
    // restrictions.
    return (*str == '\0') ? 0 : 1 + strlen_(str + 1);
#endif
  }

  constexpr const_reference at_(size_type pos) const noexcept {
    return *(begin_ + pos);
  }

  constexpr basic_string_view substr_(size_type pos = 0, size_type count = npos)
      const {
    return basic_string_view{begin_ + pos, std::min(count, size() - pos)};
  }

  constexpr bool equals_(basic_string_view rhs) const {
    // We don't use string_view::compare() here but implement it manually because
    // only looking at equality allows for more optimized code.
#if defined(__GNUC__)
    return size() == rhs.size() && 0 == __builtin_memcmp(data(), rhs.data(), size());
#elif __cpp_constexpr >= 201304
    // if we are in C++14, write it iteratively. This is faster than the recursive C++11 implementation below.
    if (size() != rhs.size()) {
      return false;
    }
    // Yes, memcmp would be laster than this loop, but memcmp isn't constexpr
    // and I didn't feel like implementing a constexpr memcmp variant.
    // TODO At some point this should probably be done, including tricks
    // like comparing one machine word instead of a byte per iteration.
    for (typename basic_string_view<CharT>::size_type pos = 0; pos < size();
         ++pos) {
      if (at_(pos) != rhs.at_(pos)) {
        return false;
      }
    }
    return true;
#else
    // if we are in C++11, we need to do it recursively because of constexpr
    // restrictions.
    return (size() != rhs.size()) ? false
                                  : (size() == 0)
            ? true
            : (front() != rhs.front()) ? false
                                       : (substr_(1).equals_(rhs.substr_(1)));
#endif
  }

  const_pointer begin_;
  size_type size_;
};

template <class CharT>
const typename basic_string_view<CharT>::size_type basic_string_view<CharT>::npos;

template <class CharT>
inline std::basic_ostream<CharT>& operator<<(
    std::basic_ostream<CharT>& stream,
    basic_string_view<CharT> sv) {
  // The rules for operator<< are quite complex, but std::string has the same.
  // Let's just rely on the std::string implementation. This might be a bit
  // slower, but I don't think performance matters here.
  return stream << ::std::basic_string<CharT>(sv);
}

using string_view = basic_string_view<char>;

} // namespace c10


int main() {
  constexpr auto x = c10::string_view("fsdfa::fsdfas").find("fff");
}
