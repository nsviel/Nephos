#pragma once

#include <opencv2/opencv.hpp>
#include <string>


namespace rad::cal::structure{

struct Canny{
  //---------------------------

  bool apply = true;
  int thres_lower = 50;
  int thres_upper = 150;

  //---------------------------
};

}
