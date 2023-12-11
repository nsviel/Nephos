#pragma once

#include <Utility/UTL_specific/common.h>
#include <VK_struct/Namespace.h>


namespace vk::structure{

struct Framebuffer{
  //---------------------------

  //Main object
  VkFramebuffer fbo;

  //Attachment
  vk::structure::Image color;
  vk::structure::Image depth;
  vk::structure::Image location;
  vk::structure::Image normal;

  //---------------------------
};

}
