#pragma once

#include <Vulkan/VK_command/Structure/Command_buffer.h>
#include <Vulkan/VK_synchronization/Structure/Fence.h>
#include <Vulkan/VK_synchronization/Structure/Semaphore.h>
#include <Vulkan/VK_binding/Structure/Descriptor.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <mutex>


namespace vk::pool::structure{

struct Descriptor{
  //---------------------------

  std::mutex mutex;
  VkDescriptorPool allocator = VK_NULL_HANDLE;
  std::vector<vk::structure::Descriptor> tank;
  uint32_t size = 100;

  //---------------------------
};

}
