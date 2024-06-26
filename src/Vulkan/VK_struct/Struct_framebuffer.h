#pragma once

#include <Vulkan/VK_struct/Struct_image.h>
#include <vulkan/vulkan.h>


namespace vk::structure{

struct Framebuffer{
  //---------------------------

  //Main object
  VkFramebuffer handle = VK_NULL_HANDLE;

  //Attachment
  vk::structure::Image color;
  vk::structure::Image color_resolve;
  vk::structure::Image depth;
  vk::structure::Image location;
  vk::structure::Image normal;

  //---------------------------
};

}
