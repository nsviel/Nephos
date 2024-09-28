#pragma once

#include <Vulkan/Core/VK_binding/Structure/Uniform.h>
#include <Vulkan/Core/VK_binding/Structure/Pushconst.h>
#include <Vulkan/Core/VK_binding/Structure/Sampler.h>
#include <Vulkan/Core/VK_binding/Structure/Storage.h>
#include <vulkan/vulkan.h>
#include <unordered_map>
#include <memory>
#include <vector>


namespace vk::structure{

struct Descriptor_set{
  //---------------------------

  VkDescriptorSet handle = VK_NULL_HANDLE;

  //Associated descriptor
  std::unordered_map<std::string, std::shared_ptr<vk::structure::Pushconst>> map_pushcst;
  std::unordered_map<std::string, std::shared_ptr<vk::structure::Uniform>> map_uniform;
  std::unordered_map<std::string, std::shared_ptr<vk::structure::Sampler>> map_sampler;
  std::unordered_map<std::string, std::shared_ptr<vk::structure::Storage>> map_storage;

  //---------------------------
};

}
