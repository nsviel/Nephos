#pragma once

#include <Vulkan/Graphics/Compute/Structure.h>
#include <Vulkan/Graphics/Render/Structure.h>


namespace vk::graphics{

struct Structure{
  //---------------------------

  vk::gfx::compute::Structure compute;
  vk::gfx::render::Structure render;

  //---------------------------
};

}
