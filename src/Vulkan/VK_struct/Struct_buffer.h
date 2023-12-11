#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

struct Buffer{
  //---------------------------

  VkBuffer vbo = VK_NULL_HANDLE;
  VkDeviceMemory mem = VK_NULL_HANDLE;

  //---------------------------
};

}
