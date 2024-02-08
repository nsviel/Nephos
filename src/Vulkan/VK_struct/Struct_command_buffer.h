#pragma once

#include <Utility/Specific/common.h>
#include <Vulkan/VK_struct/Struct_fence.h>


namespace vk::structure{

struct Command_buffer{
  //---------------------------

  //Command
  VkCommandBuffer command = VK_NULL_HANDLE;
  vk::structure::Fence* fence = nullptr;
  bool is_available = true;
  bool is_recorded = false;
  bool is_resetable = true;

  //---------------------------
};

}
