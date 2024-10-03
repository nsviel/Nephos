#pragma once

#include <Vulkan/Core/VK_synchronization/Structure/Fence.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <mutex>


namespace vk::pool::structure{

struct Fence{
  //---------------------------

  std::vector<vk::structure::Fence> tank;
  std::mutex mutex;
  uint32_t size = 100;

  //---------------------------
};

}
