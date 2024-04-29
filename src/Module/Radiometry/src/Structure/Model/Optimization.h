#pragma once

#include <string>
#include <vector>


namespace radio::structure{

struct Optimization{
  //---------------------------

  std::string path = "../media/record/calibration/model.json";
  std::string serial_number = "";
  std::string method = "";

  utl::type::Axis x;
  utl::type::Axis y;

  float rmse = 0;
  int degree_x = 6;
  int degree_y = 2;

  //---------------------------
};

}
