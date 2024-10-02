#pragma once

#include <Vulkan/Core/VK_synchronization/Structure/Fence.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <mutex>


namespace vk::pool::structure{

struct Fence{
  //---------------------------

  std::mutex mutex;
  std::vector<vk::synchro::structure::Fence> tank;
  uint32_t size = 100;

  //---------------------------
};

}
