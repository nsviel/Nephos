#pragma once

#include <vulkan/vulkan.h>


namespace vk::pipeline::structure{

struct Shader{
  //---------------------------

  VkShaderModule vs;
  VkShaderModule fs;

  //---------------------------
};

}
