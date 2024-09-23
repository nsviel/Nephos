#pragma once

#include <Vulkan/Render/VK_render/Structure/Pipeline.h>
#include <Vulkan/Render/VK_render/Structure/Presentation.h>
#include <Vulkan/Render/VK_render/Structure/Renderpass.h>


namespace vk::render{

struct Structure{
  //---------------------------

  vk::render::structure::Pipeline pipeline;
  vk::render::structure::Renderpass renderpass;
  vk::render::structure::Presentation presentation;

  //---------------------------
};

}
