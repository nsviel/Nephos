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
  void clean();

  //Fence function
  void create_fence(vk::structure::Fence* fence);
  void clean_fence(vk::structure::Fence* fence);
  void reset_fence(vk::structure::Fence* fence);

  //Subfunction
  vk::structure::Fence* query_free_fence();
  bool is_fence_available(VkFence& fence);

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
