#pragma once

#include <Utility/Specific/Common.h>
#include <Radiometry/Namespace.h>
#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Radiometry/src/Detection/Structure/Hough.h>
#include <Radiometry/src/Detection/Structure/Canny.h>
#include <Radiometry/src/Detection/Structure/Bbox.h>
#include <Radiometry/src/Detection/Structure/Ransac.h>
#include <Radiometry/src/Detection/Structure/Sphere.h>


namespace rad::structure{

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

  rad::structure::Hough hough;
  rad::structure::Canny canny;
  rad::structure::Bbox bbox;
  rad::structure::Ransac ransac;

  //---------------------------
};

}
