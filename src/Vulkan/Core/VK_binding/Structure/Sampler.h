#pragma once

#include <vulkan/vulkan.h>
#include <string>


namespace vk::descriptor::structure{

struct Sampler{
  //---------------------------

  std::string name = "";
  int binding = 0;
  VkDescriptorType type = VK_DESCRIPTOR_TYPE_SAMPLER;

  //---------------------------
};

}
