#include <cstring>
#include <limits>
#include <stdexcept>
#include <string>
#include <algorithm>

template <class CharT>
class basic_string_view final {
 public:
  static constexpr int npos = int(-1);

  constexpr basic_string_view() noexcept : begin_(nullptr), size_(0) {}

  explicit constexpr basic_string_view(const char *str, int count)
      : begin_(str), size_(count) {}

  /* implicit */ constexpr basic_string_view(const char *str)
      : basic_string_view(str, strlen_(str)) {}

  constexpr int find() const noexcept {
    substr_(1).equals_(substr_(1));
    return 0;
  }

  constexpr int find(const char *s, int pos = 0) const {
    return find(basic_string_view(s), pos);
  }

  static constexpr int strlen_(const char *str) noexcept {
    const char *current = str;
    while (*current != '\0') {
      ++current;
    }
    return current - str;
  }

  constexpr basic_string_view substr_(int pos = 0, int count = npos)
      const {
    return basic_string_view{begin_ + pos, std::min(count, size_ - pos)};
  }

  constexpr bool equals_(basic_string_view rhs) const {
    return size_ == rhs.size_ && 0 == __builtin_memcmp(begin_, rhs.begin_, size_);
  }

  const char *begin_;
  int size_;
};

using string_view = basic_string_view<char>;

int main() {
  constexpr auto x = string_view("fsdfa::fsdfas").find();
}
