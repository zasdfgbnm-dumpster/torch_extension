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

  constexpr size_type find() const noexcept {
    substr_(1).equals_(substr_(1));
    return 0;
  }

  constexpr size_type find(const_pointer s, size_type pos = 0) const {
    return find(basic_string_view(s), pos);
  }

  static constexpr size_type strlen_(const_pointer str) noexcept {
    const_pointer current = str;
    while (*current != '\0') {
      ++current;
    }
    return current - str;
  }

  constexpr basic_string_view substr_(size_type pos = 0, size_type count = npos)
      const {
    return basic_string_view{begin_ + pos, std::min(count, size_ - pos)};
  }

  constexpr bool equals_(basic_string_view rhs) const {
    return size_ == rhs.size_ && 0 == __builtin_memcmp(begin_, rhs.begin_, size_);
  }

  const_pointer begin_;
  size_type size_;
};

using string_view = basic_string_view<char>;

int main() {
  constexpr auto x = string_view("fsdfa::fsdfas").find();
}
