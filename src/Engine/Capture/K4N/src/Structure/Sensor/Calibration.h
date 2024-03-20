#pragma once

#include <Scene/Namespace.h>
#include <opencv2/opencv.hpp>
#include <string>


namespace k4n::structure{

struct Calibration{
  //---------------------------

  cv::Mat cv_image;
  cv::Point cv_center;
  int cv_radius;

  vector<vec3> vec_circle;
  vector<glyph::scene::Sphere*> vec_sphere_glyph;

  //---------------------------
};

}
