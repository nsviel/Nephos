#pragma once

#include <Scene/Namespace.h>
#include <opencv2/opencv.hpp>
#include <string>


namespace k4n::structure{

struct Calibration{
  //---------------------------

  cv::Mat cv_image;
  cv::Mat cv_subimage;
  cv::Point cv_center;
  float sphere_diameter = 0.1;
  float cv_BB_scale = 2;
  int cv_radius = 0;

  vector<vec3> vec_circle;
  vector<glyph::scene::Sphere*> vec_sphere_glyph;

  //---------------------------
};

}
