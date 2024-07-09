#pragma once

#include <Vulkan/VK_binding/Structure/Binding.h>
#include <Utility/Base/Shader/Info.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>


//Binding requirement -> Name, Type size, binding, desriptor type, shader stage
typedef std::vector<std::tuple<std::string, std::size_t, int, VkDescriptorType, VkShaderStageFlagBits>> vec_descriptor_required;


namespace vk::pipeline::structure{

struct Definition{
  //---------------------------

  //Info
  std::string name = "";
  std::string topology = "";
  std::string purpose = "";

  utl::shader::Info* shader;
  std::vector<std::string> vec_data_name;
  vec_descriptor_required binding;

  //---------------------------
};

}
