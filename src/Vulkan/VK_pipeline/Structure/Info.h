#pragma once

#include <Vulkan/VK_pipeline/Structure/Enum.h>
#include <Utility/Base/Shader/Info.h>
#include <Utility/Base/Data/Topology.h>
#include <vector>


namespace vk::pipeline::structure{

struct Info{
  //---------------------------

  std::vector<vk::pipeline::Attribut> vec_attribut;
  utl::topology::Type topology = utl::topology::POINT;
  utl::shader::Info* shader;

  //---------------------------
};

}
