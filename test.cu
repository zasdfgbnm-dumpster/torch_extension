#include <cstring>
#include <limits>
#include <stdexcept>
#include <string>
#include <algorithm>

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
  }

  constexpr size_type find(const_pointer s, size_type pos = 0) const {
    return find(basic_string_view(s), pos);
  }

  static constexpr size_type strlen_(const_pointer str) noexcept {
    // if we are in C++14, write it iteratively. This is faster.
    const_pointer current = str;
    while (*current != '\0') {
      ++current;
    }
    return current - str;
  }

  constexpr const_reference at_(size_type pos) const noexcept {
    return *(begin_ + pos);
  }

  constexpr basic_string_view substr_(size_type pos = 0, size_type count = npos)
      const {
    return basic_string_view{begin_ + pos, std::min(count, size() - pos)};
  }

  constexpr bool equals_(basic_string_view rhs) const {
    return size() == rhs.size() && 0 == __builtin_memcmp(data(), rhs.data(), size());
  }

  const_pointer begin_;
  size_type size_;
};

template <class CharT>
const typename basic_string_view<CharT>::size_type basic_string_view<CharT>::npos;

using string_view = basic_string_view<char>;

int main() {
  constexpr auto x = string_view("fsdfa::fsdfas").find("fff");
}
