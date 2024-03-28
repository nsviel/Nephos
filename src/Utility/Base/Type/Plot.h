#pragma once


namespace utl::plot{

struct Axis{
  //---------------------------

  //Data
  int size = 0;
  float min = 0;
  float max = 0;
  float current = 0;
  float resolution = 0.01f;
  std::vector<float> data;
  glm::vec2 bound = vec2(0, 0);

  //---------------------------
};

}

namespace utl::type{

struct Plot{
  //---------------------------

  //Format
  std::string title = "";
  std::string x_axis_name = "";
  std::string y_axis_name = "";
  glm::ivec2 dimension = ivec2(0, 0);
  glm::vec2 highlight = vec2(-1, -1);

  //Data
  utl::plot::Axis x;
  utl::plot::Axis y;
  utl::plot::Axis z;

  //---------------------------
};

}
