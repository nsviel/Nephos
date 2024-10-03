#pragma once

#include <Vulkan/Core/VK_synchronization/Structure/Semaphore.h>
#include <vulkan/vulkan.h>
#include <memory>
#include <vector>
#include <mutex>


namespace vk::pool::structure{

struct Semaphore{
  //---------------------------

  std::vector<std::shared_ptr<vk::structure::Semaphore>> tank;
  std::mutex mutex;
  uint32_t size = 100;

  //---------------------------
};

}
