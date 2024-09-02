#pragma once

#include <Utility/Base/Data/Path.h>
#include <Utility/Base/Plot/Axis.h>
#include <string>
#include <vector>


namespace dat::sensor{

struct Model{
  //---------------------------

  std::string depth_mode = "";
  utl::base::Path path_measure;

  std::vector<float> coefficient;
  utl::base::Axis axis_x;
  utl::base::Axis axis_y;

  float rmse = 0;
  int degree_x = 3;
  int degree_y = 2;

  //---------------------------
};

struct Calibration{
  //---------------------------

  utl::base::Path path;
  std::vector<dat::sensor::Model> vec_model;

  //---------------------------
};



}
