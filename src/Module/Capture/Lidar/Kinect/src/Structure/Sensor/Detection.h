#pragma once

#include <Radiometry/Namespace.h>
#include <Scene/Namespace.h>
#include <Glyph/Namespace.h>
#include <opencv2/opencv.hpp>


namespace k4n::structure{

struct Detection{
  //---------------------------

  cv::Mat cv_image;
  cv::Mat cv_subimage;
  cv::Point cv_center;
  float sphere_diameter = 0.16;
  int cv_radius = 0;
  int nb_detection = 0;

  vector<radio::structure::Circle> vec_circle;
  vector<radio::structure::Sphere> vec_sphere;
  vector<gly::element::object::Sphere*> vec_glyph_sphere;
  gly::element::object::Sphere* glyph_calibration;

  //---------------------------
};

}
