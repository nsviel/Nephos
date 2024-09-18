#pragma once

#include <Vulkan/Core/VK_binding/Structure/Sampler.h>
#include <Vulkan/Core/VK_binding/Structure/Uniform.h>
#include <Vulkan/Core/VK_binding/Structure/Pushconst.h>
#include <vulkan/vulkan.h>
#include <unordered_map>
#include <memory>
#include <vector>


namespace vk::descriptor::structure{

struct Descriptor_set{
  //---------------------------

  VkDescriptorSet handle = VK_NULL_HANDLE;
  
  //Associated descriptor
  std::unordered_map<std::string, std::shared_ptr<vk::descriptor::structure::Pushconst>> map_pushcst;
  std::unordered_map<std::string, std::shared_ptr<vk::descriptor::structure::Uniform>> map_uniform;
  std::unordered_map<std::string, std::shared_ptr<vk::descriptor::structure::Sampler>> map_sampler;

  //---------------------------
};

}
