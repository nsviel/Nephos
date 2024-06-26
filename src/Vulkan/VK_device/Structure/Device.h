#pragma once

#include <Vulkan/VK_queue/Structure/Pool.h>
#include <Vulkan/VK_device/Structure/Physical_device.h>
#include <vulkan/vulkan.h>


namespace vk::structure{

struct Device{
  //---------------------------

  VkDevice handle = VK_NULL_HANDLE;
  vk::queue::structure::Pool queue;
  vk::structure::Physical_device physical_device;

  //---------------------------
};

}
