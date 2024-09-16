#pragma once

#include <Vulkan/Core/VK_queue/Structure/Set.h>
#include <Vulkan/Core/VK_device/Structure/Physical.h>
#include <vulkan/vulkan.h>


namespace vk::device::structure{

struct Logical{
  //---------------------------

  VkDevice handle = VK_NULL_HANDLE;
  vk::queue::structure::Set queue;
  vk::device::structure::Physical physical_device;

  //---------------------------
};

}
