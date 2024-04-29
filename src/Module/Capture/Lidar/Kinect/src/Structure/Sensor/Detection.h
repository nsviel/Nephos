#pragma once

#include <Radiometry/Namespace.h>
#include <Scene/Namespace.h>
#include <Data/Namespace.h>
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

  vector<rad::structure::Circle> vec_circle;
  vector<rad::structure::Sphere> vec_sphere;
  vector<dat::glyph::object::Sphere*> vec_glyph_sphere;
  dat::glyph::object::Sphere* glyph_calibration;

  //---------------------------
};

}
