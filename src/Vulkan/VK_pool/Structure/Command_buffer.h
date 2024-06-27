#pragma once

#include <Vulkan/VK_command/Structure/Command_buffer.h>
#include <Vulkan/VK_synchronization/Structure/Fence.h>
#include <Vulkan/VK_synchronization/Structure/Semaphore.h>
#include <Vulkan/VK_binding/Structure/Descriptor.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <mutex>


namespace vk::pool::structure{

struct Command_buffer{
  //---------------------------

  std::mutex mutex;
  VkCommandPool allocator = VK_NULL_HANDLE;
  std::vector<vk::structure::Command_buffer*> tank;
  uint32_t size = 100;
  bool is_available = true;
  std::thread::id thread_ID;

  //---------------------------
};

}
