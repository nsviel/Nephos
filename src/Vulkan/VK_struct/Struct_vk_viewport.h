#pragma once

#include <string>
#include <vulkan/vulkan.h>


namespace vk::structure{

struct Struct_vk_viewport{
  //---------------------------

  VkViewport viewport;
  VkRect2D scissor;

  //---------------------------
};

}
