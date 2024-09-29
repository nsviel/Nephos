#pragma once

#include <vulkan/vulkan.h>


namespace vk::shader::structure{

struct Module{
  //---------------------------

  VkShaderModule vs;
  VkShaderModule fs;
  VkShaderModule comp;

  //---------------------------
};

}
