#pragma once

#include <Vulkan/VK_binding/Structure/Descriptor.h>
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
  std::vector<vk::binding::structure::Required> vec_required_binding;
  std::vector<VkDescriptorSetLayoutBinding> vec_layout;
  vk::binding::structure::Descriptor descriptor;

  //Binding elements
  std::vector<vk::binding::structure::Pushconst*> vec_pushcst;
  std::vector<vk::binding::structure::Uniform*> vec_uniform;



  std::unordered_map<std::string, vk::binding::structure::Pushconst*> map_pushcst;
  std::unordered_map<std::string, vk::binding::structure::Uniform*> map_uniform;
  std::unordered_map<std::string, vk::binding::structure::Sampler*> map_sampler;

  //---------------------------
};

}
