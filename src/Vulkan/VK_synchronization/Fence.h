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
  void init();
  void create_fence(VkFence& fence);
  void clean_fence(VkFence& fence);
  
private:
  vk::structure::Vulkan* struct_vulkan;
};

}
