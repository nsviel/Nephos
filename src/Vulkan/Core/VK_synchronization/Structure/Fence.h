#pragma once

#include <vulkan/vulkan.h>


namespace vk::synchro::structure{

struct Fence{
  //---------------------------

  VkFence handle = VK_NULL_HANDLE;
  bool is_available = true;

  //---------------------------
};

}