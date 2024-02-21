#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/common.h>


namespace vk::structure{

struct Device{
  //---------------------------

  VkDevice handle;
  vk::structure::Queue_object queue;
  vk::structure::Physical_device physical_device;

  //---------------------------
};

}
