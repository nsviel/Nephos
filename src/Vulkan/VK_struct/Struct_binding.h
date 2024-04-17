#pragma once

#include <Vulkan/VK_struct/VK_typedef.h>
#include <Utility/Specific/Common.h>

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
  vec_descriptor_required vec_required_binding;
  Descriptor descriptor;

  //Binding elements
  vector<vk::structure::Push_constant*> vec_pushcst;
  vector<vk::structure::Uniform*> vec_uniform;
  vector<vk::structure::Sampler*> vec_sampler;

  //---------------------------
};

}
