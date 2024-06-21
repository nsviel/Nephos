#pragma once

#include <Utility/Base/Type/Path.h>
#include <string>
#include <vector>


namespace rad::correction::structure{

struct Model{
  //---------------------------

  //"../media/calibration/kinect.json"
  utl::base::Path path;

  std::vector<float> coefficient;
  utl::base::Axis axis_x;
  utl::base::Axis axis_y;

  float rmse = 0;
  int degree_x = 3;
  int degree_y = 2;

  //---------------------------
};

}
