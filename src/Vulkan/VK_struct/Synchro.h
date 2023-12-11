#pragma once

#include <Utility/UTL_specific/common.h>


namespace vk::structure{

struct Synchro{
  //---------------------------

  VkFence fence;
  VkSemaphore semaphore_image_ready;
  VkSemaphore semaphore_render_done;
  std::vector<VkSemaphore> vec_semaphore_render;

  //---------------------------
};

}
