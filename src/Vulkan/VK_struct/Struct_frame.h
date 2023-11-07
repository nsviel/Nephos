#ifndef STRUCT_FRAME_H
#define STRUCT_FRAME_H

#include <ELE_specific/common.h>
#include "Struct_image.h"


struct Struct_frame{
  //---------------------------

  Struct_image image;

  VkFramebuffer framebuffer;
  VkCommandBuffer command_buffer;
  VkSemaphore semaphore;

  //---------------------------
};


#endif
