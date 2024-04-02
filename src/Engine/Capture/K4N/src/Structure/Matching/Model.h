#pragma once

#include <string>
#include <vector>


namespace k4n::structure{

struct Model{
  //---------------------------

  //Model stuff
  std::string path = "../media/record/calibration_model.data";
  utl::type::Axis x;
  utl::type::Axis y;
  int degree = 2;

  //---------------------------
};

}
