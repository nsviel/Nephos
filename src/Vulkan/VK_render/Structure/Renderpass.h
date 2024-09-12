#pragma once

#include <Vulkan/VK_renderpass/Structure/Renderpass.h>


namespace vk::render::structure{

struct Renderpass{
  //---------------------------

  vk::structure::Renderpass onscreen;
  vk::structure::Renderpass offscreen;
  vk::structure::Renderpass edl;

  //---------------------------
};

}
