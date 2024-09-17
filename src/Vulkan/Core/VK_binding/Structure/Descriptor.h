#pragma once

#include <vulkan/vulkan.h>
#include <string>


namespace vk::descriptor::structure{

struct Descriptor{
  //---------------------------

  VkDescriptorType type;
  VkShaderStageFlagBits stage;
  std::string name = "";
  std::size_t size = 0;
  int binding = 0;

  //---------------------------
};

}
