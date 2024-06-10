#pragma once

#include <opencv2/opencv.hpp>
#include <string>


namespace rad::detection::structure{

struct Canny{
  //---------------------------

  bool apply = false;
  int thres_lower = 50;
  int thres_upper = 150;

  //---------------------------
};

}
