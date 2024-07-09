#pragma once

#include <Vulkan/VK_pipeline/Element/Vertex.h>
#include <Vulkan/VK_binding/Structure/Descriptor.h>
#include <Vulkan/VK_binding/Structure/Binding.h>
#include <Utility/Base/Shader/Info.h>
#include <vector>
#include <string>


namespace vk::pipeline::structure{

struct Info{
  //Information which must be defined beforhand
  //---------------------------

  std::vector<vk::pipeline::Attribut> vec_attribut;
  utl::topology::Type topology = utl::topology::POINT;
  utl::shader::Info* shader;
  std::string name = "";

  //---------------------------
};

}
