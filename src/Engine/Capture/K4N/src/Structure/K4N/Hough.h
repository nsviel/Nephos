#pragma once

#include <Scene/Namespace.h>
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

  int drawing_mode = k4n::hough::ALL;
  int mode = k4n::hough::GRADIENT;
  int cv_mode = cv::HOUGH_GRADIENT;
  int nb_detection = 0;
  int ratio = 1;
  int min_dist = 72;
  int min_radius = 5;
  int max_radius = 50;
  int canny_thres_lower = 50;
  int canny_thres_upper = 150;
  float param_1 = -1;
  float param_2 = -1;
  bool apply_canny = false;

  //---------------------------
};

}
