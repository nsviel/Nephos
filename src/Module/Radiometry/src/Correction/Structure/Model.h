#pragma once

#include <string>
#include <vector>


namespace rad::correction::structure{

struct Model{
  //---------------------------

  std::string path_dir = "../media/calibration";
  std::string name_model = "kinect.json";
  std::string name_measure = "NFOV_sphere.data";

  std::vector<float> coefficient;
  utl::base::Axis axis_x;
  utl::base::Axis axis_y;

  float rmse = 0;
  int degree_x = 3;
  int degree_y = 2;

  //---------------------------
};

}
