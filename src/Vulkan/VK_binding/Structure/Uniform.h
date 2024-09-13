#pragma once

#include <vulkan/vulkan.h>
#include <string>


namespace vk::binding::structure{

struct Uniform{
  //---------------------------

  std::string name = "";
  size_t size = 0;
  int binding = 0;
  VkBuffer buffer = VK_NULL_HANDLE;
  VkDeviceMemory mem = VK_NULL_HANDLE;
  void* mapped = nullptr;

  //---------------------------
};

}
