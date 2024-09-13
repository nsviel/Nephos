#pragma once

#include <string>
#include <vulkan/vulkan.h>


namespace vk::structure{

struct Viewport{
  //---------------------------

  VkViewport handle = {};
  VkRect2D scissor = {};

  //---------------------------
};

}
