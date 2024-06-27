#pragma once

#include <Vulkan/VK_command/Structure/Command_buffer.h>
#include <Vulkan/VK_synchronization/Structure/Fence.h>
#include <Vulkan/VK_synchronization/Structure/Semaphore.h>
#include <Vulkan/VK_binding/Structure/Descriptor.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <mutex>


namespace vk::pool{

struct Fence{
  //---------------------------

  std::mutex mutex;
  std::vector<vk::synchro::structure::Fence> tank;
  uint32_t size = 100;

  //---------------------------
};

}
