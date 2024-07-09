#pragma once

#include <Vulkan/VK_pipeline/Element/Vertex.h>
#include <Vulkan/VK_binding/Structure/Descriptor.h>
#include <Vulkan/VK_binding/Structure/Binding.h>
#include <Utility/Base/Shader/Info.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>


namespace vk::pipeline::structure{

struct Info{
  //---------------------------

  //Info
  std::string name = "";
  utl::topology::Type topology = utl::topology::POINT;

  utl::shader::Info* shader;
  std::vector<vk::pipeline::Attribut> vec_attribut;
  std::vector<vk::binding::structure::Required> binding;

  //---------------------------
};

}
