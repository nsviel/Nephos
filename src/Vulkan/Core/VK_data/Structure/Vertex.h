#pragma once

#include <Vulkan/Core/VK_data/Structure/Buffer.h>
#include <Vulkan/Core/VK_pipeline/Structure/Enum.h>


namespace vk::structure{

struct Vertex{
  //---------------------------

  vk::attribut::binding::ID binding;
  vk::structure::Buffer buffer;
  vk::structure::Buffer stagger;
  int channel = 0;
  int size_max = 0;
  int size = 0;

  //---------------------------
};

}
