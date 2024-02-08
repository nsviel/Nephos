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

  //Fence function
  void create_fence(VkFence& fence);
  void clean_fence(VkFence& fence);
  void reset_fence(VkFence& fence);

  //Subfunction
  vk::structure::Fence* query_free_fence();
  bool is_fence_available(VkFence& fence);
  
private:
  vk::structure::Vulkan* struct_vulkan;
};

}
