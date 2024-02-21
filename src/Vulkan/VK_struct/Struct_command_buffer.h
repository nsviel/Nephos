#pragma once

#include <Utility/Specific/common.h>
#include <Vulkan/VK_struct/Struct_fence.h>


namespace vk::structure{

struct Command_buffer{
  //---------------------------

  int UID = 0;

  //Command
  vk::structure::Query query;
  VkCommandBuffer command = VK_NULL_HANDLE;
  bool is_available = true;
  bool is_recorded = false;
  bool is_resetable = true;

  //---------------------------
};

}
