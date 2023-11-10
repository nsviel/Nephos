#ifndef STRUCT_INSTANCE_H
#define STRUCT_INSTANCE_H

#include <ELE_specific/common.h>


struct Struct_instance{
  //---------------------------

  VkInstance instance;
  vector<const char*> extension_ext;
  vector<const char*> extension_khr;
  int max_frame_inflight = 2;
  std::vector<VkPhysicalDevice> vec_physical_device;

  //---------------------------
};


#endif
