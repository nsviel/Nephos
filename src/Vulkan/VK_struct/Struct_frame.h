#pragma once

#include <Utility/Specific/Common.h>
#include <Vulkan/VK_struct/Namespace.h>


namespace vk::structure{

struct Frame{
  //---------------------------

  //Attachment
  vk::structure::Image color;
  vk::structure::Image depth;

  //---------------------------
};

}
