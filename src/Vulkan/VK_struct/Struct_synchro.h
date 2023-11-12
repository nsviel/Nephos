#ifndef STRUCT_SYNCHRO_H
#define STRUCT_SYNCHRO_H

#include <ELE_specific/common.h>


struct Struct_synchro{
  //---------------------------

  //VkSemaphore semaphore_image_ready;
  //VkSemaphore semaphore_render_done;
  std::vector<VkSemaphore> vec_semaphore_render;
  std::vector<VkFence> vec_fence;

  //---------------------------
};

#endif
