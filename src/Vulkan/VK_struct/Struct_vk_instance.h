#ifndef STRUCT_VK_INSTANCE_H
#define STRUCT_VK_INSTANCE_H

#include <VK_struct/Struct_vk_physical_device.h>
#include <UTL_specific/common.h>


struct Struct_vk_instance{
  //---------------------------

  VkInstance instance;
  vector<const char*> extension_instance;
  vector<const char*> extension_device;
  int max_frame_inflight = 2;
  std::vector<Struct_vk_physical_device> vec_physical_device;

  //---------------------------
};


#endif
