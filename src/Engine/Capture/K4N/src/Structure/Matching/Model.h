#pragma once


namespace k4n::structure{

struct Model{
  //---------------------------

  float min_R = 3.0f;
  float max_R = 3.0f;
  float resolution = 0.01f;
  std::vector<float> vec_R;
  std::vector<float> vec_I;

  //---------------------------
};

}
