#pragma once

#include <vulkan/vulkan.h>
#include <string>


namespace vk::binding::structure{

struct Descriptor{
  //---------------------------

  //Consistent attribut binding:
  //  -position -> 0
  //  -color -> 1
  //  -uv -> 2
  //  -normal -> 3
  //  -depth -> 4
  //  -uniform -> 5

  std::string name = "";
  std::size_t size = 0;
  int binding = 0;

  VkDescriptorType type;
  VkShaderStageFlagBits stage;

  //---------------------------
};

}
