#pragma once


namespace utl::type{

struct Plot{
  //---------------------------

  //Data
  int x_size = 0;
  float x_min = 0.0f;
  float x_max = 3.0f;
  float x_resolution = 0.01f;
  std::vector<float> vec_x;

  int y_size = 0;
  float y_min = 0.0f;
  float y_max = 3.0f;
  float y_resolution = 0.01f;
  std::vector<float> vec_y;

  int z_size = 0;
  float z_min = 0.0f;
  float z_max = 3.0f;
  float z_resolution = 0.01f;
  std::vector<float> vec_z;

  //Format
  std::string title = "";
  std::string x_axis_name = "";
  std::string y_axis_name = "";
  glm::ivec2 dimension = ivec2(0, 0);
  glm::vec2 highlight = vec2(-1, -1);

  //---------------------------
};

}
