#pragma once

#include <glm/glm.hpp>


namespace vk::image{

enum Screenshot_format{
  BMP = 0,
  JPEG = 1,
  BIN = 2,
};

struct Structure{
  //---------------------------

  //Screenshot parameters
  vk::image::Screenshot_format screenshot_format = vk::image::BMP;
  glm::vec2 screenshot_dim =  glm::vec2(4096, 2000);

  //---------------------------
};

}
