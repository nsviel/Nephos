#ifndef STRUCT_VK_FRAMEBUFFER_H
#define STRUCT_VK_FRAMEBUFFER_H

#include <UTL_specific/common.h>
#include <VK_struct/Struct_vk_image.h>


struct Struct_vk_framebuffer{
  //---------------------------

  //Main object
  VkFramebuffer fbo;

  //Attachment
  Struct_vk_image color;
  Struct_vk_image depth;
  Struct_vk_image location;
  Struct_vk_image normal;

  //---------------------------
};


#endif
