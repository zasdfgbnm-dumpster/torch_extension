#include <torch/library.h>

struct CuaevComputer : torch::CustomClassHolder {};

TORCH_LIBRARY(cuaev, m) {
  m.class_<CuaevComputer>("CuaevComputer");
}
