#pragma once

#include <Vulkan/Core/VK_synchronization/Structure/Semaphore.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <mutex>


namespace vk::pool::structure{

struct Semaphore{
  //---------------------------

  std::mutex mutex;
  std::vector<vk::structure::Semaphore> tank;
  uint32_t size = 100;

  //---------------------------
};

}
