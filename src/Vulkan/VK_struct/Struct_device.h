#ifndef STRUCT_DEVICE_H
#define STRUCT_DEVICE_H

#include <VK_struct/Struct_physical_device.h>
#include <ELE_specific/common.h>


struct Struct_device{
  //---------------------------

  VkDevice device;
  VkQueue queue_graphics;
  VkQueue queue_presentation;
  Struct_physical_device struct_device;

  uint32_t nb_queue_family;
  int queue_graphics_idx;
  int queue_presentation_idx;

  //---------------------------
};


#endif
