#pragma once

#include <Utility/Base/Type/Plot.h>
#include <string>
#include <vector>


namespace rad::calibration::structure{

struct Optimization{
  //---------------------------

  std::string path = "../media/calibration/model.json";
  std::string serial_number = "";
  std::string method = "";
  std::vector<float> coefficient;

  utl::base::Axis axis_x;
  utl::base::Axis axis_y;

  float rmse = 0;
  int degree_x = 3;
  int degree_y = 2;

  //---------------------------
};

}
