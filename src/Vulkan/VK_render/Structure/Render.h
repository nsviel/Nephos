#pragma once

#include <Vulkan/VK_renderpass/Structure/Renderpass.h>
#include <Vulkan/VK_render/Structure/Renderpass.h>
#include <Vulkan/VK_render/Structure/EDL.h>
#include <vulkan/vulkan.h>
#include <vector>


namespace vk::render::structure{

struct Render{
  //---------------------------

  vk::render::structure::EDL edl;

  //---------------------------
};

}