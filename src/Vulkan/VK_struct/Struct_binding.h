#pragma once

#include <Vulkan/VK_struct/VK_typedef.h>
#include <Utility/Specific/Common.h>


namespace vk::structure{

//Structures
struct Uniform{
  //---------------------------

  std::string name = "";
  size_t size = 0;
  int binding = 0;
  VkBuffer buffer = VK_NULL_HANDLE;
  VkDeviceMemory mem = VK_NULL_HANDLE;
  void* mapped = nullptr;

  //---------------------------
};

struct Sampler{
  //---------------------------

  std::string name = "";
  int binding = 0;
  VkDescriptorType type = VK_DESCRIPTOR_TYPE_SAMPLER;

  //---------------------------
};

struct Push_constant{
  //---------------------------

  std::string name = "";
  int binding = 0;
  VkShaderStageFlagBits stage = VK_SHADER_STAGE_VERTEX_BIT;

  //---------------------------
};

struct Binding{
  //---------------------------

  //Binding description
  std::vector<vk::structure::Descriptor_required> vec_required_binding;
  Descriptor descriptor;

  //Binding elements
  vector<vk::structure::Push_constant*> vec_pushcst;
  vector<vk::structure::Uniform*> vec_uniform;
  vector<vk::structure::Sampler*> vec_sampler;

  //---------------------------
};

}
