#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}


namespace vk::presentation{

class Surface
{
public:
  //Constructor / Destructor
  Surface(vk::structure::Vulkan* struct_vulkan);
  ~Surface();

public:
  //Main functions
  void init();
  void clean();

  //Subfunction
  void check_for_resizing();
  vec2 compute_window_dim();

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
