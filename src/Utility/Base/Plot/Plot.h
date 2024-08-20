#pragma once

#include <Utility/Base/Plot/Axis.h>
#include <glm/glm.hpp>
#include <string>


namespace utl::base{

struct Plot{
  //---------------------------

  //Format
  std::string title = "";
  std::string axis_x_name = "";
  std::string axis_y_name = "";
  glm::ivec2 dimension = glm::ivec2(0, 0);
  glm::vec2 highlight = glm::vec2(0, 0);

  //Data
  utl::base::Axis axis_x;
  utl::base::Axis axis_y;
  utl::base::Axis axis_z;

  //---------------------------
};

}
