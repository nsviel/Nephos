#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>


namespace utl::base{

struct Axis{
  //---------------------------

  //Data
  int size = 0;
  float min = 0;
  float max = 0;
  float current = 0;
  float resolution = 0;
  std::vector<float> data;
  std::vector<float> fitting;
  glm::vec2 bound = glm::vec2(0, 0);

  //---------------------------
};

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
