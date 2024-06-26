#pragma once

#include <string>
#include <vulkan/vulkan.h>


namespace vk::structure{

struct Viewport{
  //---------------------------

  VkViewport viewport = {};
  VkRect2D scissor = {};

  //---------------------------
};

}
