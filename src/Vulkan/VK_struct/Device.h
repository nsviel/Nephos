#pragma once

#include <VK_struct/Struct_vk_physical_device.h>
#include <UTL_specific/common.h>


namespace vk::structure{

struct Device{
  //---------------------------

  VkDevice device;
  VkQueue queue_graphics;
  VkQueue queue_presentation;
  Struct_vk_physical_device struct_device;

  //---------------------------
};

}
