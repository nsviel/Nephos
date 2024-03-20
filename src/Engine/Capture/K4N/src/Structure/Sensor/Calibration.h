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

struct Calibration{
  //---------------------------

  cv::Mat cv_image;
  cv::Mat cv_subimage;
  cv::Point cv_center;
  float sphere_diameter = 0.1;
  float cv_BB_scale = 2;
  int cv_radius = 0;
  int drawing_mode = k4n::hough::ALL;
  int hough_mode = k4n::hough::GRADIENT;

  vector<vec3> vec_circle;
  vector<glyph::scene::Sphere*> vec_sphere_glyph;

  //---------------------------
};

}
