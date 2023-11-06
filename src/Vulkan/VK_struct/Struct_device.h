#ifndef STRUCT_DEVICE_H
#define STRUCT_DEVICE_H

#include <ELE_specific/common.h>


struct Struct_device{
  //---------------------------

  VkPhysicalDevice physical_device;
  VkDevice device;
  VkQueue queue_graphics;
  VkQueue queue_presentation;
  vector<const char*> extension;

  vector<string> vec_device_name;
  int nb_queue_graphics;
  int nb_queue_presentation;

  //---------------------------
};


#endif
