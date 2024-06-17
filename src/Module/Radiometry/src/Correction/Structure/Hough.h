#pragma once

#include <Radiometry/src/Correction/Detection/Structure/Circle.h>
#include <Radiometry/src/Correction/Detection/Glyph/Sphere.h>
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

namespace rad::correction::structure{

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
  int min_radius = 3;
  int max_radius = 300;

  //Result
  int nb_detection = 0;
  std::vector<rad::correction::structure::Circle> vec_circle;
  std::vector<rad::correction::glyph::Sphere*> vec_glyph;

  //---------------------------
};

}
