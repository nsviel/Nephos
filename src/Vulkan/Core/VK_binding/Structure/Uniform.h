#pragma once

#include <vulkan/vulkan.h>
#include <string>


namespace vk::descriptor::structure{

struct Uniform{
  //---------------------------

  VkDeviceMemory mem = VK_NULL_HANDLE;
  VkBuffer buffer = VK_NULL_HANDLE;
  void* mapped = nullptr;
  std::string name = "";
  std::size_t size = 0;
  int binding = 0;

  //---------------------------
};

}
