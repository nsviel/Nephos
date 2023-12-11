#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/common.h>


namespace vk::structure{

struct Device{
  //---------------------------

  VkDevice device;
  VkQueue queue_graphics;
  VkQueue queue_presentation;
  vk::structure::Physical_device struct_device;

  //---------------------------
};

}
