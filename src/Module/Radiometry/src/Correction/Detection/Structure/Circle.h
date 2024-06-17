#pragma once

#include <opencv2/opencv.hpp>
#include <string>


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
