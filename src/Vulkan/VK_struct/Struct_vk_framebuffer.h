#ifndef STRUCT_FRAMEBUFFER_H
#define STRUCT_FRAMEBUFFER_H

#include <UTL_specific/common.h>
#include <VK_struct/Struct_image.h>


struct Struct_vk_framebuffer{
  //---------------------------

  //Main object
  VkFramebuffer fbo;

  //Attachment
  Struct_image color;
  Struct_image depth;
  Struct_image location;
  Struct_image normal;

  //---------------------------
};


#endif
