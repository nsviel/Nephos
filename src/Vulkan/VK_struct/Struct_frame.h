#pragma once

#include <Utility/Specific/common.h>
#include <Vulkan/VK_struct/Namespace.h>


namespace vk::structure{

struct Frame{
  //---------------------------

  //Main object
  VkFramebuffer fbo;
  VkSemaphore semaphore_image_ready;
  std::vector<VkSemaphore> vec_semaphore_render;

  //Attachment
  Image color;
  Image depth;

  //---------------------------
};

}
