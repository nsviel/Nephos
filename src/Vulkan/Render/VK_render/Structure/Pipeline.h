#pragma once

#include <Vulkan/Render/VK_renderpass/Postprocess/Descriptor/EDL.h>


namespace vk::render::structure{

struct Pipeline{
  //---------------------------

  vk::postprocess::EDL edl;

  //---------------------------
};

}