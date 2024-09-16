#pragma once

#include <Vulkan/Render/VK_engine/Structure/Profiler.h>
#include <Vulkan/Render/VK_pipeline/Structure/Structure.h>
#include <Vulkan/Render/VK_renderpass/Structure/Renderpass.h>
#include <Vulkan/Render/VK_engine/Structure/Parameter.h>


namespace vk::render{

struct Structure{
  //---------------------------

  vk::structure::Parameter param;
  vk::profiler::Structure profiler;
  vk::render::pipeline::Structure render;
  vk::render::structure::Renderpass renderpass;

  //---------------------------
};

}
