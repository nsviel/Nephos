#pragma once

#include <Vulkan/Core/VK_synchronization/Structure/Fence.h>
#include <vulkan/vulkan.h>
#include <memory>
#include <vector>
#include <mutex>


namespace vk::pool::structure{

struct Fence{
  //---------------------------

  std::vector<std::shared_ptr<vk::structure::Fence>> tank;
  std::mutex mutex;
  uint32_t size = 100;

  //---------------------------
};

}
