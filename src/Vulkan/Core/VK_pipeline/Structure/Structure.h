#pragma once

#include <Vulkan/Core/VK_pipeline/Structure/Pipeline.h>
#include <unordered_map>


namespace vk::pipeline{

struct Structure{
  //---------------------------

  std::unordered_map<std::string, vk::structure::Pipeline*> map;

  //---------------------------
};

}
