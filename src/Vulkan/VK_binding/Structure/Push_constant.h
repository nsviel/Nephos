#pragma once

#include <vulkan/vulkan.h>
#include <string>


namespace vk::binding::structure{

struct Push_constant{
  //---------------------------

  std::string name = "";
  int binding = 0;
  VkShaderStageFlagBits stage = VK_SHADER_STAGE_VERTEX_BIT;

  //---------------------------
};

}
