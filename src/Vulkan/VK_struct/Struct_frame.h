#pragma once

#include <Utility/Specific/common.h>
#include <Vulkan/VK_struct/Namespace.h>


namespace vk::structure{

struct Frame{
  //---------------------------

  //Main object
  VkFramebuffer fbo;

  //Attachment
  Image color;
  Image depth;

  //---------------------------
};

}
