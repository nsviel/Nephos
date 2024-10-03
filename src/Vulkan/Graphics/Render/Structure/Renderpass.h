#pragma once

#include <Vulkan/Core/VK_renderpass/Structure/Renderpass.h>


namespace vk::render::structure{

struct Renderpass{
  //---------------------------

  vk::structure::Renderpass geometry;
  vk::structure::Renderpass postprocess;
  vk::structure::Renderpass presentation;

  //---------------------------
};

}
