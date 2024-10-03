#pragma once

#include <Vulkan/Core/VK_renderpass/Structure/Renderpass.h>
#include <memory>
#include <vector>


namespace vk::drawer{

struct Structure{
  //---------------------------

  std::vector<vk::structure::Renderpass*> vec_renderpass;

  //---------------------------
};

}
