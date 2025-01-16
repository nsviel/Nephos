#pragma once

#include <Vulkan/Core/VK_renderpass/Structure/Renderpass.h>
#include <memory>
#include <vector>


namespace vk::render{

struct Structure{
  //---------------------------

  std::vector<std::shared_ptr<vk::structure::Renderpass>> vec_renderpass;

  //---------------------------
};

}
