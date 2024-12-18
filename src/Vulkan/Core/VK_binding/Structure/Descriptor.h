#pragma once

#include <vulkan/vulkan.h>
#include <string>


namespace vk::structure{

struct Descriptor{
  //---------------------------

  std::string name = "";
  std::size_t size = 0;
  VkDescriptorType type;
  VkShaderStageFlagBits stage;
  int binding = 0;

  //---------------------------
};

}
