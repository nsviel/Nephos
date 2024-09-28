#pragma once

#include <Vulkan/Core/VK_command/Structure/Command_buffer.h>
#include <Vulkan/Core/VK_synchronization/Structure/Fence.h>
#include <Vulkan/Core/VK_synchronization/Structure/Semaphore.h>
#include <Vulkan/Core/VK_binding/Structure/Descriptor.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <mutex>


namespace vk::pool::structure{

struct Descriptor_set{
  //---------------------------

  std::vector<vk::structure::Descriptor_set> tank;
  std::mutex mutex;
  VkDescriptorPool pool = VK_NULL_HANDLE;
  uint32_t size = 100;

  //---------------------------
};

}
