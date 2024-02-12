#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

struct Semaphore{
  //---------------------------

  VkSemaphore semaphore = VK_NULL_HANDLE;
  bool is_available = true;

  //---------------------------
};

}
