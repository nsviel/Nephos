#pragma once

#include <Vulkan/Core/VK_renderpass/Structure/Renderpass.h>
#include <memory>


namespace vk::render::structure{

struct Renderpass{
  //---------------------------

  std::shared_ptr<vk::structure::Renderpass> geometry = std::make_shared<vk::structure::Renderpass>();
  std::shared_ptr<vk::structure::Renderpass> postprocess = std::make_shared<vk::structure::Renderpass>();
  std::shared_ptr<vk::structure::Renderpass> presentation = std::make_shared<vk::structure::Renderpass>();

  //---------------------------
};

}
