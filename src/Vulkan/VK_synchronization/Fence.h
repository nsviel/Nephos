#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Fence;}


namespace vk::synchro{

class Fence
{
public:
  //Constructor / Destructor
  Fence(vk::structure::Vulkan* struct_vulkan);
  ~Fence();

public:
  //Main functions
  void init();

  //Subfunction
  vk::structure::Fence* query_free_fence();
  void create_fence(VkFence& fence);
  void clean_fence(VkFence& fence);

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
