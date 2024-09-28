#pragma once

#include <Vulkan/Graphics/Render/Structure/Pipeline.h>
#include <Vulkan/Graphics/Render/Structure/Presentation.h>
#include <Vulkan/Graphics/Render/Structure/Renderpass.h>


namespace vk::render{

struct Structure{
  //---------------------------

  vk::render::structure::Pipeline pipeline;
  vk::render::structure::Renderpass renderpass;
  vk::render::structure::Presentation presentation;

  //---------------------------
};

}
