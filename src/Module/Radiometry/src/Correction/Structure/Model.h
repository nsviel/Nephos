#pragma once

#include <string>
#include <vector>


namespace rad::correction::structure{

struct Model{
  //---------------------------

  std::string path_dir = "../media/calibration";
  std::string name_model = "kinect.json";
  std::string name_measure = "NFOV_sphere.data";

  std::string device = "Kinect";
  std::string serial_number = "9999999";
  std::string depth_mode = "NFOV";

  std::vector<float> coefficient;
  std::vector<std::string> mode;
  utl::base::Axis axis_x;
  utl::base::Axis axis_y;

  float rmse = 0;
  int degree_x = 3;
  int degree_y = 2;

  //---------------------------
};

}
