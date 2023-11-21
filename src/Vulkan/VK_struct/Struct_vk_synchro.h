#ifndef STRUCT_VK_SYNCHRO_H
#define STRUCT_VK_SYNCHRO_H

#include <UTL_specific/common.h>


struct Struct_vk_synchro{
  //---------------------------

  VkFence fence;
  VkSemaphore semaphore_image_ready;
  VkSemaphore semaphore_render_done;
  std::vector<VkSemaphore> vec_semaphore_render;

  //---------------------------
};

#endif
