#pragma once

#include <vulkan/vulkan.h>
#include <vector>


namespace vk::descriptor::structure{

struct Descriptor_set{
  //---------------------------

  VkDescriptorSet handle = VK_NULL_HANDLE;

  //Associated descriptor descriptions
  std::vector<VkWriteDescriptorSet> vec_write_descriptor_set;
  std::vector<VkDescriptorBufferInfo> vec_descriptor_buffer_info;

  //---------------------------
};

}
