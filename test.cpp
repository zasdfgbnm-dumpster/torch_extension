template <class CurClass>
class class_ {};

class Library {
public:
  template <class CurClass>
  inline class_<CurClass> class_() { return {}; }
};

class CuaevComputer {};

int main() {
  Library().class_<CuaevComputer>();
}
