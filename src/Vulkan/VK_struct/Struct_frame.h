#ifndef STRUCT_FRAME_H
#define STRUCT_FRAME_H

#include <ELE_specific/common.h>
#include <VK_struct/Struct_image.h>


struct Struct_frame{
  //---------------------------

  Struct_image image;

  VkFramebuffer framebuffer;
  VkCommandBuffer command_buffer;
  VkSemaphore semaphore;

  //A suprimer !!!
  VkFramebuffer fbo;
  Struct_image color;
  Struct_image depth;
  Struct_image location;
  Struct_image normal;

  //---------------------------
};


#endif
