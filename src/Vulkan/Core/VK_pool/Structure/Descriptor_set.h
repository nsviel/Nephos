#pragma once

#include <Vulkan/Core/VK_binding/Structure/Descriptor_set.h>
#include <memory>
#include <vector>
#include <mutex>


namespace vk::pool::structure{

struct Descriptor_set{
  //---------------------------

  std::mutex mutex;
  std::vector<std::shared_ptr<vk::structure::Descriptor_set>> tank;
  uint32_t size = 100;

  //---------------------------
};

}
