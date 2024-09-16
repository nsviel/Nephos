#pragma once

#include <Vulkan/Core/VK_pipeline/Structure/Pipeline.h>
#include <Utility/Base/Data/Topology.h>
#include <unordered_map>


namespace vk::pipeline{

struct Structure{
  //---------------------------

  std::unordered_map<utl::topology::Type, vk::structure::Pipeline*> map;

  //---------------------------
};

}
