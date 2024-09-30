#pragma once

#include <Vulkan/Graphics/Compute/Structure/Structure.h>
#include <Vulkan/Graphics/Render/Structure/Structure.h>


namespace vk::graphics{

struct Structure{
  //---------------------------

  vk::compute::Structure compute;
  vk::render::Structure render;

  //---------------------------
};

}
