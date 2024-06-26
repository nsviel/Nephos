#pragma once

#include <glm/glm.hpp>
#include <string>


namespace prf::base{

struct Task{
  //---------------------------

  glm::vec4 color = glm::vec4(0, 0, 0, 0);
  std::string name;
  double ts_begin;
  double ts_end;

  //---------------------------
};

}
