#pragma once

#include <Vulkan/Core/VK_pipeline/Structure/Pipeline.h>
#include <Utility/Base/Data/Topology.h>
#include <unordered_map>
#include <memory>
#include <string>


namespace vk::pipeline{

struct Structure{
  //---------------------------

  std::unordered_map< utl::topology::Type, std::shared_ptr<vk::structure::Pipeline> > map_topology;
  std::unordered_map< std::string, std::shared_ptr<vk::structure::Pipeline> > map_compute;

  //---------------------------
};

}
