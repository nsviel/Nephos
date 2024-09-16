#pragma once

#include <Vulkan/Render/VK_pipeline/Structure.h>
#include <Vulkan/Render/VK_renderpass/Structure/Renderpass.h>


namespace vk::render{

struct Structure{
  //---------------------------

  vk::render::pipeline::Structure pipeline;
  vk::render::structure::Renderpass renderpass;

  //---------------------------
};

}
