#pragma once

#include <vulkan/vulkan.h>


namespace vk::structure{

struct Semaphore{
  //---------------------------

  VkSemaphore handle = VK_NULL_HANDLE;
  bool is_available = true;

  //---------------------------
};

}
