#pragma once

#include <VK_struct/Namespace.h>
#include <Utility/UTL_specific/common.h>


namespace vk::structure{

struct Instance{
  //---------------------------

  VkInstance instance;
  vector<const char*> extension_instance;
  vector<const char*> extension_device;
  int max_frame_inflight = 2;
  std::vector<vk::structure::Physical_device> vec_physical_device;

  //---------------------------
};

}
