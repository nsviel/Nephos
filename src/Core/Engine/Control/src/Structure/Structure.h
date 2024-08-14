#pragma once

#include <Control/src/Structure/Wheel.h>
#include <glm/glm.hpp>
#include <string>


namespace ctr{

struct Structure{
  //---------------------------

  glm::vec2 cursor_pose = glm::vec2(0, 0);
  float speed_translation = 0.01;
  float speed_fast = 0.05;
  bool key_fast = false;
  int wheel_mode = ctr::wheel::CAM_Z;

  //---------------------------
};

}
