#pragma once


namespace utl::type{

struct Plot{
  //---------------------------

  //Data
  int size = 0;
  glm::vec2 highlight = vec2(-1, -1);

  float x_min = 0.0f;
  float x_max = 3.0f;
  float x_resolution = 0.01f;
  std::vector<float> vec_x;

  float y_min = 0.0f;
  float y_max = 3.0f;
  float y_resolution = 0.01f;
  std::vector<float> vec_y;

  //Format
  std::string title = "";
  std::string x_axis_name = "";
  std::string y_axis_name = "";
  glm::ivec2 dimension = ivec2(0, 0);

  //---------------------------
};

}
