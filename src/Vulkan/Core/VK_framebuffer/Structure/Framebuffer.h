#pragma once

#include <Vulkan/Core/VK_image/Structure/Image.h>
#include <vulkan/vulkan.h>


namespace vk::structure{

struct Framebuffer{
  //---------------------------

  //Main object
  VkFramebuffer handle = VK_NULL_HANDLE;
  std::vector<VkImageView> vec_attachment;
  int width = 1;
  int height = 1;

  //Attachment
  vk::structure::Image color;
  vk::structure::Image color_resolve;
  vk::structure::Image depth;
  vk::structure::Image location;
  vk::structure::Image normal;

  //---------------------------
};

}
