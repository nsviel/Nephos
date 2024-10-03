#pragma once

#include <vulkan/vulkan.h>


namespace vk::structure{

struct Buffer{
  //---------------------------

  VkBuffer vbo = VK_NULL_HANDLE;
  VkDeviceMemory mem = VK_NULL_HANDLE;
  VkDeviceSize size = 0;

  //---------------------------
};

}
