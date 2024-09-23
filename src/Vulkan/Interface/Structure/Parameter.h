#pragma once

#include <glm/glm.hpp>


namespace vk::structure{

struct Parameter{
  //---------------------------

  glm::vec4 background_color = glm::vec4(0.4f, 0.4f, 0.4f, 1);
  glm::vec2 headless_dim =  glm::vec2(1024, 500);
  bool headless = false;

  //---------------------------
};

}
