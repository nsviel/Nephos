#pragma once

#include <Utility/UTL_specific/common.h>
#include <Vulkan/VK_struct/Image.h>


namespace vk::structure{

struct Frame{
  //---------------------------

  //Main object
  VkFramebuffer fbo;
  VkFence fence;
  VkSemaphore semaphore_image_ready;
  VkSemaphore semaphore_render_done;
  std::vector<VkSemaphore> vec_semaphore_render;

  //Attachment
  Image image;
  Image depth;

  //---------------------------
};

}
