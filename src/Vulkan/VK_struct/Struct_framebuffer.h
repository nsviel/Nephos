#pragma once

#include <Utility/Specific/Common.h>
#include <Vulkan/VK_struct/Namespace.h>


namespace vk::structure{

struct Framebuffer{
  //---------------------------

  //Main object
  VkFramebuffer fbo;

  //Attachment
  vk::structure::Image color;
  vk::structure::Image color_resolve;
  vk::structure::Image depth;
  vk::structure::Image location;
  vk::structure::Image normal;

  //---------------------------
};

}
