#pragma once

#include <vulkan/vulkan.h>
#include <string>


namespace vk::binding::structure{

struct Descriptor_set{
  //---------------------------

  VkDescriptorSetLayout layout = VK_NULL_HANDLE;
  VkDescriptorSet set = VK_NULL_HANDLE;
  bool is_available = true;

  //---------------------------
};

}
