#pragma once

#include <vulkan/vulkan.h>
#include <string>


namespace vk::structure{

struct Uniform{
  //---------------------------

  std::string name = "";
  std::size_t size = 0;
  VkDeviceMemory mem = VK_NULL_HANDLE;
  VkBuffer buffer = VK_NULL_HANDLE;
  void* mapped = nullptr;
  int binding = 0;

  //---------------------------
};

}
