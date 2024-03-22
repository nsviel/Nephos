#pragma once

#include <opencv2/opencv.hpp>
#include <string>


namespace k4n::hough{

enum Drawing{
  ALL = 0,
  BEST = 1,
};

enum Mode{
  GRADIENT = 0,
  GRADIENT_ALT = 1,
};

}

namespace k4n::structure{

struct Hough{
  //---------------------------

  bool apply = true;
  int drawing_mode = k4n::hough::ALL;
  int mode = k4n::hough::GRADIENT_ALT;
  int cv_mode = cv::HOUGH_GRADIENT;

  float param_1 = -1;
  float param_2 = -1;
  int ratio = 1;
  int min_dist = 72;
  int min_radius = 5;
  int max_radius = 50;

  //---------------------------
};

}
