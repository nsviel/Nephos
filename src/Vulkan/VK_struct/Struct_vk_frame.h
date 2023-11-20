#ifndef STRUCT_FRAME_H
#define STRUCT_FRAME_H

#include <UTL_specific/common.h>
#include <VK_struct/Struct_vk_image.h>


struct Struct_vk_frame{
  //---------------------------

  //Main object
  VkFramebuffer fbo;
  VkFence fence;
  VkSemaphore semaphore_image_ready;
  VkSemaphore semaphore_render_done;
  std::vector<VkSemaphore> vec_semaphore_render;

  //Attachment
  Struct_vk_image image;
  Struct_vk_image depth;

  //---------------------------
};


#endif
