#pragma once

#include <Vulkan/Core/VK_binding/Structure/Descriptor.h>
#include <Vulkan/Core/VK_binding/Structure/Sampler.h>
#include <Vulkan/Core/VK_binding/Structure/Uniform.h>
#include <Vulkan/Core/VK_binding/Structure/Pushconst.h>
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
  std::unordered_map<std::string, vk::descriptor::structure::Pushconst*> map_pushcst;
  std::unordered_map<std::string, vk::descriptor::structure::Uniform*> map_uniform;
  std::unordered_map<std::string, vk::descriptor::structure::Sampler*> map_sampler;

  //---------------------------
};

}
