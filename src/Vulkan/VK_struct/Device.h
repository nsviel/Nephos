#pragma once

#include <VK_struct/Physical_device.h>
#include <UTL_specific/common.h>


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
