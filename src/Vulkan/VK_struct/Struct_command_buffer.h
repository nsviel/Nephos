#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

struct Command_buffer{
  //---------------------------

  //Command
  VkCommandBuffer command = VK_NULL_HANDLE;
  bool is_available = true;
  bool is_recorded = false;

  //---------------------------
};

}
