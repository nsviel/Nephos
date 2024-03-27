#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/Common.h>


namespace vk::structure{

struct Device{
  //---------------------------

  VkDevice handle = VK_NULL_HANDLE;
  vk::structure::queue::Pool queue;
  vk::structure::Physical_device physical_device;

  //---------------------------
};

}
