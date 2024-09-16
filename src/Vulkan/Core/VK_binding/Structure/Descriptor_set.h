#pragma once

#include <vulkan/vulkan.h>


namespace vk::descriptor::structure{

struct Descriptor_set{
  //---------------------------

  VkDescriptorSet handle = VK_NULL_HANDLE;
  bool is_available = true;

  //---------------------------
};

}
