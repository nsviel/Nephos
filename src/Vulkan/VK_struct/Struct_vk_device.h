#ifndef STRUCT_VK_DEVICE_H
#define STRUCT_VK_DEVICE_H

#include <VK_struct/Struct_vk_physical_device.h>
#include <UTL_specific/common.h>


struct Struct_vk_device{
  //---------------------------

  VkDevice device;
  VkQueue queue_graphics;
  VkQueue queue_presentation;
  Struct_vk_physical_device struct_device;

  //---------------------------
};


#endif
