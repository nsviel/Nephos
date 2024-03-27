#pragma once

#include <Utility/Specific/Common.h>
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
