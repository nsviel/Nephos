#pragma once

#include <Vulkan/VK_struct/Struct_physical_device.h>
#include <vulkan/vulkan.h>


namespace vk::structure{

struct Device{
  //---------------------------

  VkDevice handle = VK_NULL_HANDLE;
  vk::structure::queue::Pool queue;
  vk::structure::Physical_device physical_device;

  //---------------------------
};

}
