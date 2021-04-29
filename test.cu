#include <torch/library.h>

void test() {}

TORCH_LIBRARY_IMPL(torchvision, CUDA, m) {
  m.impl(
      TORCH_SELECTIVE_NAME("torchvision::roi_pool"),
      TORCH_FN(test));
  m.impl(
      TORCH_SELECTIVE_NAME("torchvision::_roi_pool_backward"),
      TORCH_FN(test));
}