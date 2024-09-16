#pragma once

#include <Vulkan/Render/VK_pipeline/Structure.h>
#include <Vulkan/Render/VK_renderpass/Structure/Renderpass.h>
#include <Vulkan/Render/VK_engine/Structure/Parameter.h>


namespace vk::render{

struct Structure{
  //---------------------------

  vk::structure::Parameter param;
  vk::render::pipeline::Structure pipeline;
  vk::render::structure::Renderpass renderpass;

  //---------------------------
};

}
