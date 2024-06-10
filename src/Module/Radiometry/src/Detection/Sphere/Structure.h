#pragma once

#include <Utility/Specific/Common.h>
#include <Radiometry/Namespace.h>
#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Radiometry/src/Detection/Sphere/Structure/Circle.h>
#include <Radiometry/src/Detection/Sphere/Structure/Hough.h>
#include <Radiometry/src/Detection/Sphere/Structure/Canny.h>
#include <Radiometry/src/Detection/Sphere/Structure/Ransac.h>
#include <Radiometry/src/Detection/Sphere/Structure/Sphere.h>
#include <Radiometry/src/Detection/Sphere/Glyph/Sphere.h>


namespace rad::detection::sphere{

struct Structure{
  //---------------------------

  cv::Mat cv_image;
  cv::Mat cv_subimage;
  cv::Point cv_center;
  float sphere_diameter = 0.139;
  int cv_radius = 0;
  int nb_detection = 0;
  utl::media::Image image;
  int state_step = rad::detection::VALIDATION;
  int state_data = rad::detection::NO_DATA;

  vector<rad::detection::structure::Circle> vec_circle;
  vector<rad::detection::structure::Sphere> vec_sphere;
  vector<rad::detection::glyph::Sphere*> vec_glyph_sphere;
  rad::detection::glyph::Sphere* glyph_calibration;

  rad::detection::structure::Hough hough;
  rad::detection::structure::Canny canny;
  rad::detection::structure::Bbox bbox;
  rad::detection::structure::Ransac ransac;

  //---------------------------
};

}
