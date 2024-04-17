#pragma once

#include <Utility/Specific/Common.h>


namespace vk::structure{

struct Fence{
  //---------------------------

  VkFence handle = VK_NULL_HANDLE;
  bool is_available = true;

  //---------------------------
};

}
