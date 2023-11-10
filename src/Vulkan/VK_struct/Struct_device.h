#ifndef STRUCT_DEVICE_H
#define STRUCT_DEVICE_H

#include <VK_struct/Struct_physical_device.h>
#include <ELE_specific/common.h>


struct Struct_device{
  //---------------------------

  VkDevice device;
  VkPhysicalDevice physical_device;
  VkQueue queue_graphics;
  VkQueue queue_presentation;
  Struct_physical_device* physical_device_;

  vector<string> vec_device_name;
  uint32_t nb_queue_family;
  int queue_graphics_idx;
  int queue_presentation_idx;

  //---------------------------
};


#endif
