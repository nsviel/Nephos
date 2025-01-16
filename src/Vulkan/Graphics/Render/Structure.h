#pragma once

#include <Vulkan/Core/VK_renderpass/Structure/Renderpass.h>
#include <memory>


namespace vk::gfx::render{

struct Renderpass{
  //---------------------------

  std::shared_ptr<vk::structure::Renderpass> geometry = std::make_shared<vk::structure::Renderpass>();
  std::shared_ptr<vk::structure::Renderpass> postprocess = std::make_shared<vk::structure::Renderpass>();
  std::shared_ptr<vk::structure::Renderpass> presentation = std::make_shared<vk::structure::Renderpass>();

  //---------------------------
};

struct Structure{
  //---------------------------

  vk::gfx::edl::Structure edl_struct;
  vk::structure::Texture presentation;
  vk::structure::Texture depth;
  vk::gfx::render::Renderpass renderpass;

  //---------------------------
};

}
