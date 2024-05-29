#pragma once

#include <opencv2/opencv.hpp>
#include <string>


namespace rad::hough{

enum Drawing{
  ALL = 0,
  BEST = 1,
};

enum Mode{
  GRADIENT = 0,
  GRADIENT_ALT = 1,
};

}

namespace rad::detection::structure{

struct Hough{
  //---------------------------

  int drawing_mode = rad::hough::ALL;
  int mode = rad::hough::GRADIENT_ALT;
  int cv_mode = cv::HOUGH_GRADIENT;

  float param_1 = -1;
  float param_2 = -1;
  int ratio = 1;
  int min_dist = 72;
  int min_radius = 5;
  int max_radius = 50;

  //---------------------------
};

struct Canny{
  //---------------------------

  bool apply = false;
  int lower_threshold = 50;
  int upper_threshold = 150;

  //---------------------------
};

struct Circle{
  //---------------------------

  int radius;
  glm::ivec2 center;

  //---------------------------
};

struct Bbox{
  //---------------------------

  float scale = 2;

  //---------------------------
};

}
