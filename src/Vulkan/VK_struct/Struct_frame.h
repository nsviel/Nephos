#pragma once

#include <Utility/Specific/common.h>
#include <Vulkan/VK_struct/Namespace.h>


namespace vk::structure{

struct Frame{
  //---------------------------

  //Main object
  VkFramebuffer fbo;
  VkSemaphore semaphore_image_ready;
  VkSemaphore semaphore_render_done;
  std::vector<VkSemaphore> vec_semaphore_render;
  vk::structure::Fence* fence = nullptr;

  //Attachment
  Image color;
  Image depth;

  //---------------------------
};

}
