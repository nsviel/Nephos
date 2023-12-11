#pragma once

#include <VK_struct/Struct_vk_physical_device.h>
#include <UTL_specific/common.h>


namespace vk::structure{

struct Instance{
  //---------------------------

  VkInstance instance;
  vector<const char*> extension_instance;
  vector<const char*> extension_device;
  int max_frame_inflight = 2;
  std::vector<Struct_vk_physical_device> vec_physical_device;

  //---------------------------
};

}
