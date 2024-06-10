#pragma once

#include <Utility/Specific/Common.h>
#include <Radiometry/Namespace.h>
#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Radiometry/src/Detection/Sphere/Structure/Data.h>
#include <Radiometry/src/Detection/Sphere/Structure/Circle.h>
#include <Radiometry/src/Detection/Sphere/Structure/Hough.h>
#include <Radiometry/src/Detection/Sphere/Structure/Canny.h>
#include <Radiometry/src/Detection/Sphere/Structure/Ransac.h>


namespace rad::detection::sphere{

struct Structure{
  //---------------------------

  cv::Mat cv_image;
  cv::Mat cv_subimage;
  cv::Point cv_center;
  int cv_radius = 0;
  utl::media::Image image;




  //Step
  int state_step = rad::detection::VALIDATION;
  int state_data = rad::detection::NO_DATA;

  //Structures
  rad::detection::structure::Data data;
  rad::detection::structure::Hough hough;
  rad::detection::structure::Canny canny;
  rad::detection::structure::Bbox bbox;
  rad::detection::structure::Ransac ransac;

  //---------------------------
};

}
