#ifndef STRUCT_VK_VIEWPORT_H
#define STRUCT_VK_VIEWPORT_H

#include <string>
#include <vulkan/vulkan.h>


struct Struct_vk_viewport{
  //---------------------------

  VkViewport viewport;
  VkRect2D scissor;

  //---------------------------
};


#endif
