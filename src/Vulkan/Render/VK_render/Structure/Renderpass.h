#pragma once

#include <Vulkan/Core/VK_renderpass/Structure/Renderpass.h>
#include <vector>


namespace vk::render{

struct Renderpass{
  //---------------------------

  std::vector<vk::structure::Renderpass*> vec_renderpass;
  vk::structure::Renderpass geometry;
  vk::structure::Renderpass postprocess;
  vk::structure::Renderpass presentation;

  //---------------------------
};

}
