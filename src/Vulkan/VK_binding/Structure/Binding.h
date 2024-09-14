#pragma once

#include <Vulkan/VK_binding/Structure/Descriptor.h>
#include <Vulkan/VK_binding/Structure/Descriptor_set.h>
#include <Vulkan/VK_binding/Structure/Sampler.h>
#include <Vulkan/VK_binding/Structure/Uniform.h>
#include <Vulkan/VK_binding/Structure/Pushconst.h>
#include <vulkan/vulkan.h>
#include <unordered_map>
#include <vector>


namespace vk::binding::structure{

struct Binding{
  //---------------------------

  //Binding description
  std::vector<vk::binding::structure::Descriptor> vec_descriptor;
  std::vector<VkDescriptorSetLayoutBinding> vec_layout;
  vk::binding::structure::Descriptor_set descriptor_set;

  //Binding elements
  std::unordered_map<std::string, vk::binding::structure::Pushconst*> map_pushcst;
  std::unordered_map<std::string, vk::binding::structure::Uniform*> map_uniform;
  std::unordered_map<std::string, vk::binding::structure::Sampler*> map_sampler;

  //---------------------------
};

}
