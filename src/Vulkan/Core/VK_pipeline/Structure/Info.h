#pragma once

#include <Vulkan/Core/VK_pipeline/Structure/Enum.h>
#include <Utility/Base/Data/Topology.h>
#include <vector>
#include <string>


namespace vk::pipeline::structure{

struct Info{
  //---------------------------

  std::string name = "";
  std::vector<vk::attribut::ID> vec_attribut;
  utl::topology::Type topology = utl::topology::POINT;

  //---------------------------
};

}
