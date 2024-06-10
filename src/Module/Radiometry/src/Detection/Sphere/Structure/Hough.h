#pragma once

#include <opencv2/opencv.hpp>
#include <string>


namespace rad::hough{

enum Mode{
  GRADIENT = 0,
  GRADIENT_ALT = 1,
};

enum Drawing{
  ALL = 0,
  BEST = 1,
};

}

namespace rad::detection::structure{

struct Hough{
  //---------------------------

  //Mode
  int draw = rad::hough::ALL;
  int mode = rad::hough::GRADIENT_ALT;
  int cv_mode = cv::HOUGH_GRADIENT;

  //Parameter
  float param_1 = -1;
  float param_2 = -1;
  int ratio = 1;
  int min_dist = 72;
  int min_radius = 5;
  int max_radius = 50;

  //Result
  int nb_detection = 0;

  //---------------------------
};

}