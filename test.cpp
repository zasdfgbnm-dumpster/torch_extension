#include <torch/custom_class.h>

struct CuaevComputer : torch::CustomClassHolder {};

void f(torch::Library& m) {
  m.class_<CuaevComputer>("CuaevComputer");
}
