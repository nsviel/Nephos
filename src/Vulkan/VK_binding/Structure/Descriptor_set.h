#pragma once

#include <vulkan/vulkan.h>
#include <string>


namespace vk::binding::structure{

struct Descriptor_set{
  //---------------------------

  VkDescriptorSet handle = VK_NULL_HANDLE;
  VkDescriptorSetLayout layout = VK_NULL_HANDLE;
  bool is_available = true;

  //---------------------------
};

}
