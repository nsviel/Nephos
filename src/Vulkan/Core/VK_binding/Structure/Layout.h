#pragma once

#include <Vulkan/Core/VK_binding/Structure/Descriptor.h>
#include <vulkan/vulkan.h>
#include <unordered_map>
#include <vector>


namespace vk::descriptor::structure{

struct Layout{
  //---------------------------

  //Binding description
  VkDescriptorSetLayout handle = VK_NULL_HANDLE;
  std::vector<VkDescriptorSetLayoutBinding> vec_binding;

  //Binding elements
  std::vector<vk::descriptor::structure::Descriptor> vec_descriptor;

  //---------------------------
};

}
