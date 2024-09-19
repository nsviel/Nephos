#pragma once

#include <Vulkan/Render/VK_render/Structure/Pipeline.h>
#include <Vulkan/Render/VK_render/Structure/Renderpass.h>


namespace vk::render{

struct Structure{
  //---------------------------

  vk::render::Pipeline pipeline;
  vk::render::Renderpass renderpass;

  //---------------------------
};

}
