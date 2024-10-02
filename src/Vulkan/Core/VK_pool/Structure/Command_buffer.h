#pragma once

#include <Vulkan/Core/VK_command/Structure/Command_buffer.h>
#include <vulkan/vulkan.h>
#include <thread>
#include <vector>
#include <mutex>


namespace vk::pool::structure{

struct Command_buffer{
  //---------------------------

  std::vector<std::shared_ptr<vk::structure::Command_buffer>> tank;
  std::thread::id thread_ID;
  std::mutex mutex;

  VkCommandPool allocator = VK_NULL_HANDLE;
  uint32_t size = 100;
  bool is_available = true;

  //---------------------------
};

}
