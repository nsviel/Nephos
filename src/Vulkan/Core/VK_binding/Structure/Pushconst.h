#pragma once

#include <vulkan/vulkan.h>
#include <string>


namespace vk::descriptor::structure{

struct Pushconst{
  //---------------------------

  std::string name = "";
  int binding = 0;
  VkShaderStageFlagBits stage = VK_SHADER_STAGE_VERTEX_BIT;

  //---------------------------
};

}
