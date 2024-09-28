#pragma once

#include <vulkan/vulkan.h>
#include <string>


namespace vk::structure{

struct Pushconst{
  //---------------------------

  std::string name = "";
  VkShaderStageFlagBits stage = VK_SHADER_STAGE_VERTEX_BIT;
  int binding = 0;

  //---------------------------
};

}
