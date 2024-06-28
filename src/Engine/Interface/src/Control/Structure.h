#pragma once

#include <glm/glm.hpp>
#include <string>


namespace itf::control{

struct Structure{
  //---------------------------

  glm::vec2 cursor_pose = glm::vec2(0, 0);
  bool cam_fast = false;

  //---------------------------
};

}
