#pragma once

#include <vulkan/vulkan.h>
#include <vector>


namespace vk::descriptor::structure{

struct Descriptor_set{
  //---------------------------

  std::vector<VkWriteDescriptorSet> vec_descriptor_write;
  std::vector<VkDescriptorBufferInfo> vec_descriptor_buffer_info;
  VkDescriptorSet handle = VK_NULL_HANDLE;
  bool is_available = true;

  //---------------------------
};

}
