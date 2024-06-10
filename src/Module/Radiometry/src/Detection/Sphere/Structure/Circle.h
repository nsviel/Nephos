#pragma once

#include <opencv2/opencv.hpp>
#include <string>


namespace rad::hough{

enum Drawing{
  ALL = 0,
  BEST = 1,
};

}

namespace rad::detection::structure{

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
