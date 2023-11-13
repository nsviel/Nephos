#ifndef STRUCT_DEVICE_H
#define STRUCT_DEVICE_H

#include <VK_struct/Struct_physical_device.h>
#include <UTL_specific/common.h>


struct Struct_device{
  //---------------------------

  VkDevice device;
  VkQueue queue_graphics;
  VkQueue queue_presentation;
  Struct_physical_device struct_device;

  //---------------------------
};


#endif
