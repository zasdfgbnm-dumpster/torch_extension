#include <cstring>
#include <limits>
#include <stdexcept>
#include <string>
#include <algorithm>

class string_view final {
 public:
  static constexpr int npos = int(-1);

  constexpr int find() const noexcept {
    substr_(1).equals_(substr_(1));
    return 0;
  }
  constexpr string_view substr_(int pos = 0, int count = npos)
      const {
    return string_view{begin_ + pos, std::min(count, size_ - pos)};
  }

  constexpr bool equals_(string_view rhs) const {
    return size_ == rhs.size_ && 0 == __builtin_memcmp(begin_, rhs.begin_, size_);
  }

  const char *begin_ = "12345";
  int size_ = 5;
};

int main() {
  constexpr auto x = string_view().find();
}
