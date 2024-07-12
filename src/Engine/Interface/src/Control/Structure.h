#pragma once

#include <Interface/src/Control/Module/Wheel.h>
#include <glm/glm.hpp>
#include <string>


namespace itf::control{

struct Structure{
  //---------------------------

  glm::vec2 cursor_pose = glm::vec2(0, 0);
  float speed_translation = 0.01;
  float speed_fast = 0.05;
  bool key_fast = false;
  int wheel_mode = itf::control::WHEEL_CAM_Z;

  //---------------------------
};

}
