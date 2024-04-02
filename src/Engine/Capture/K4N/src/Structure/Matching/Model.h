#pragma once

#include <string>
#include <vector>


namespace k4n::structure{

struct Model{
  //---------------------------

  //Model stuff
  std::string path = "../media/record/calibration/model.data";
  utl::type::Axis x;
  utl::type::Axis y;
  float rmse = 0;
  int degree = 6;

  //---------------------------
};

}
