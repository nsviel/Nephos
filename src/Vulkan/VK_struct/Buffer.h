#pragma once

#include <Utility/UTL_specific/common.h>


namespace vk::structure{

struct Buffer{
  //---------------------------

  VkBuffer vbo = VK_NULL_HANDLE;
  VkDeviceMemory mem = VK_NULL_HANDLE;

  //---------------------------
};

}
