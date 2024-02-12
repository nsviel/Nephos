#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

struct Synchro{
  //---------------------------

  vk::structure::Fence* fence = nullptr;
  VkSemaphore semaphore_image_ready;
  VkSemaphore semaphore_render_done;
  std::vector<VkSemaphore> vec_semaphore_render;

  //---------------------------
};

}
