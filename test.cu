template <class CurClass>
class class_;

class Library final {
public:
  template <class CurClass>
  inline class_<CurClass> class_() {}
};

template <class CurClass>
class class_ {};

struct CuaevComputer {};

int main() {
  Library().class_<CuaevComputer>();
}
