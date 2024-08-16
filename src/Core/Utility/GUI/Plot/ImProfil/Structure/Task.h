#pragma once

#include <glm/glm.hpp>
#include <string>


namespace utl::improfil{

struct Task{
  //---------------------------

  glm::vec4 color = glm::vec4(0, 0, 0, 0);
  std::string name = "";
  double ts_begin = -1;
  double ts_end = -1;

  //---------------------------
};

}
