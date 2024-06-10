#pragma once

#include <opencv2/opencv.hpp>
#include <string>


namespace rad::detection::structure{

struct Canny{
  //---------------------------

  bool apply = false;
  int lower_threshold = 50;
  int upper_threshold = 150;

  //---------------------------
};

}
