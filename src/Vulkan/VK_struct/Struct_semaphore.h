#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

struct Semaphore{
  //---------------------------

  VkSemaphore begin = VK_NULL_HANDLE;
  VkSemaphore end = VK_NULL_HANDLE;
  bool is_available = true;

  //---------------------------
};

}
