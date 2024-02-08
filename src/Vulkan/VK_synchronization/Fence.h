#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}


namespace vk::command{

class Fence
{
public:
  //Constructor / Destructor
  Fence(vk::structure::Vulkan* struct_vulkan);
  ~Fence();

public:
  //Main functions

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
