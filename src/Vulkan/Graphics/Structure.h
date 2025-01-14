#pragma once

#include <Vulkan/Graphics/Compute/Structure.h>
#include <Vulkan/Graphics/Render/Structure.h>


namespace vk::graphics{

struct Structure{
  //---------------------------

  vk::compute::Structure compute;
  vk::render::Structure render;

  //---------------------------
};

}
