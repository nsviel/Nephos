#pragma once

#include <Vulkan/Core/VK_image/Screenshot/Format.h>
#include <glm/glm.hpp>


namespace vk::image{

struct Structure{
  //---------------------------

  //Screenshot parameters
  vk::screenshot::Formats screenshot_format = vk::screenshot::BMP;
  glm::vec2 screenshot_dim =  glm::vec2(4096, 2000);

  //---------------------------
};

}
