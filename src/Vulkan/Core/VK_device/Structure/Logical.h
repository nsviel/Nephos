#pragma once

#include <Vulkan/Core/VK_queue/Structure/Queue_set.h>
#include <Vulkan/Core/VK_device/Structure/Physical.h>
#include <vulkan/vulkan.h>


namespace vk::structure{

struct Logical{
  //---------------------------

  VkDevice handle = VK_NULL_HANDLE;
  vk::structure::Queue_set queue;
  vk::structure::Physical physical_device;

  //---------------------------
};

}
