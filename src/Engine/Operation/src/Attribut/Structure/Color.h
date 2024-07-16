#pragma once

#include <glm/glm.hpp>


namespace ope::attribut{

struct Color{
  //---------------------------

  glm::vec4 unicolor = glm::vec4(1, 1, 1, 1);
  glm::vec2 range = glm::vec2(0, 5);
  int mode = ope::color::RGB;

  //---------------------------
};

}
