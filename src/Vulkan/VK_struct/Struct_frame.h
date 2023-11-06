#ifndef STRUCT_FRAME_H
#define STRUCT_FRAME_H

#include <ELE_specific/common.h>
#include "Struct_image.h"


struct Struct_frame{
  //---------------------------

  int ID;

  //Main object
  VkFramebuffer fbo;

  //Attachment
  Struct_image color;
  Struct_image location;
  Struct_image normal;
  Struct_image depth;

  //---------------------------
};

struct Frame{
  //---------------------------

  VkImage image;
  VkImageView image_view;
  VkFramebuffer framebuffer;
  VkCommandBuffer command_buffer;
  VkSemaphore semaphore;

  //---------------------------
};


#endif
