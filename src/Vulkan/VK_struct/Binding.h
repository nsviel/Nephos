#pragma once

#include <Vulkan/VK_struct/VK_typedef.h>
#include <Utility/UTL_specific/common.h>

//Consistent attribut binding:
//  -position -> 0
//  -color -> 1
//  -uv -> 2
//  -normal -> 3
//  -depth -> 4
//  -uniform -> 5


//Binding requirement -> Name, Type size, binding, desriptor type, shader stage
typedef std::vector<std::tuple<std::string, std::size_t, int, VkDescriptorType, VkShaderStageFlagBits>> vec_descriptor_required;
typedef std::tuple<std::string, std::size_t, int, VkDescriptorType, VkShaderStageFlagBits> descriptor_required;

namespace vk::structure{

//Structures
struct Descriptor{
  //---------------------------

  VkDescriptorSetLayout layout;
  VkDescriptorSet set;

  //---------------------------
};

struct Uniform{
  //---------------------------

  std::string name;
  size_t size;
  int binding;
  VkBuffer buffer;
  VkDeviceMemory mem;
  void* mapped;

  //---------------------------
};

struct Sampler{
  //---------------------------

  std::string name;
  int binding;
  VkDescriptorType type;

  //---------------------------
};

struct Push_constant{
  //---------------------------

  std::string name;
  int binding;
  VkShaderStageFlagBits stage;

  //---------------------------
};

struct Binding{
  //---------------------------

  //Binding description
  vec_descriptor_required vec_required_binding;
  Descriptor descriptor;

  //Binding elements
  vector<vk::structure::Push_constant*> vec_pushcst;
  vector<vk::structure::Uniform*> vec_uniform;
  vector<vk::structure::Sampler*> vec_sampler;

  //---------------------------
};

}
