#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/common.h>


namespace vk::structure{

struct Device{
  //---------------------------

  VkDevice handle = VK_NULL_HANDLE;
  vk::structure::queue::ID queue;
  vk::structure::Physical_device physical_device;

  //---------------------------
};

}
