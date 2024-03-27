#pragma once


namespace utl::type{

struct Plot{
  //---------------------------

  float x_min = 0.0f;
  float x_max = 3.0f;
  float x_resolution = 0.01f;
  std::vector<float> vec_x;
  std::vector<float> vec_y;
  string x_axis_name = "";
  string y_axis_name = "";

  //---------------------------
};

}
