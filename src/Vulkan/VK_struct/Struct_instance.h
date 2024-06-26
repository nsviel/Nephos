#pragma once

#include <Vulkan/VK_struct/Struct_physical_device.h>
#include <vulkan/vulkan.h>
#include <vector>


namespace vk::structure{

struct Instance{
  //---------------------------

  VkInstance handle = VK_NULL_HANDLE;

  int max_frame_inflight = 2;
  std::vector<const char*> extension_instance;
  std::vector<const char*> extension_device;
  std::vector<vk::structure::Physical_device> vec_physical_device;

  //---------------------------
};

}
