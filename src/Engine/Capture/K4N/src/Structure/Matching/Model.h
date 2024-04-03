#pragma once

#include <string>
#include <vector>


namespace k4n::structure{

struct Model{
  //---------------------------

  //Model stuff
  std::string path = "../media/record/calibration/model.json";
  std::string serial_number = "";
  utl::type::Axis x;
  utl::type::Axis y;
  float rmse = 0;
  int degree = 6;

  //---------------------------
};

}
