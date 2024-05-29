#pragma once

#include <Utility/Specific/Common.h>
#include <Radiometry/Namespace.h>
#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Radiometry/src/Detection/Structure/Image.h>
#include <Radiometry/src/Detection/Structure/Cloud.h>


namespace rad::detection{

struct Structure{
  //---------------------------

  cv::Mat cv_image;
  cv::Mat cv_subimage;
  cv::Point cv_center;
  float sphere_diameter = 0.16;
  int cv_radius = 0;
  int nb_detection = 0;
  utl::media::Image image;

  vector<rad::detection::structure::Circle> vec_circle;
  vector<rad::detection::structure::Sphere> vec_sphere;
  vector<dat::glyph::object::Sphere*> vec_glyph_sphere;
  dat::glyph::object::Sphere* glyph_calibration;

  rad::detection::structure::Hough hough;
  rad::detection::structure::Canny canny;
  rad::detection::structure::Bbox bbox;
  rad::detection::structure::Ransac ransac;

  //---------------------------
};

}
