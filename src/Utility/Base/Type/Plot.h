#pragma once


namespace utl::type{

struct Axis{
  //---------------------------

  //Data
  int size = 0;
  float min = 0;
  float max = 0;
  float current = 0;
  float resolution = 0.01f;
  std::vector<float> data;
  std::vector<float> fitting;
  glm::vec2 bound = vec2(0, 0);

  //---------------------------
};

struct Plot{
  //---------------------------

  //Format
  std::string title = "";
  std::string x_axis_name = "";
  std::string y_axis_name = "";
  glm::ivec2 dimension = ivec2(0, 0);
  glm::vec2 highlight = vec2(-1, -1);

  //Data
  utl::type::Axis x;
  utl::type::Axis y;
  utl::type::Axis z;

  //---------------------------
};

}
