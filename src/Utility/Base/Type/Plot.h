#pragma once


namespace utl::type{

struct Plot{
  //---------------------------

  //Data
  int size = 0;
  float x_min = 0.0f;
  float x_max = 3.0f;
  float x_resolution = 0.01f;
  std::vector<float> vec_x;
  std::vector<float> vec_y;
  glm::vec2 highlight = vec2(-1, -1);

  //Format
  std::string title = "";
  std::string x_axis_name = "";
  std::string y_axis_name = "";
  glm::ivec2 dimension = ivec2(0, 0);

  //---------------------------
};

}
