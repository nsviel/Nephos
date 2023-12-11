#pragma once

#include <UTL_specific/common.h>
#include <VK_struct/Namespace.h>


namespace vk::structure{

struct Struct_vk_framebuffer{
  //---------------------------

  //Main object
  VkFramebuffer fbo;

  //Attachment
  vk::structure::Struct_vk_image color;
  vk::structure::Struct_vk_image depth;
  vk::structure::Struct_vk_image location;
  vk::structure::Struct_vk_image normal;

  //---------------------------
};

}
