#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

struct Fence{
  //---------------------------

  VkFence fence = VK_NULL_HANDLE;
  bool is_available = true;

  //---------------------------
};

}
