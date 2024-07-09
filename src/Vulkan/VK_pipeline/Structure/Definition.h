#pragma once

#include <Vulkan/VK_binding/Structure/Descriptor.h>
#include <Vulkan/VK_binding/Structure/Binding.h>
#include <Utility/Base/Shader/Info.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>


namespace vk::pipeline::structure{

struct Definition{
  //---------------------------

  //Info
  std::string name = "";
  std::string topology = "";
  std::string purpose = "";

  utl::shader::Info* shader;
  std::vector<std::string> vec_data_name;
  std::vector<vk::binding::structure::Required> binding;

  //---------------------------
};

}
