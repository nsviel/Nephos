#pragma once

#include <glm/glm.hpp>
#include <string>


namespace itf::control{

struct Structure{
  //---------------------------

  glm::vec2 cursor_pose = glm::vec2(0, 0);
  float element_trans = 0.01;
  bool key_fast = false;
  int wheel_mode = 2;

  //---------------------------
};

}
