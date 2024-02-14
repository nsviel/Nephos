#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/common.h>


namespace vk::structure{

struct Device{
  //---------------------------

  VkDevice device;
  vk::structure::Queue queue;
  vk::structure::Physical_device physical_device;

  //---------------------------
};

}
