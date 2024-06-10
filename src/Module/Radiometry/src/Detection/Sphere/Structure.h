#pragma once

#include <Radiometry/src/Detection/Sphere/Structure/Circle.h>
#include <Radiometry/src/Detection/Sphere/Structure/Hough.h>
#include <Radiometry/src/Detection/Sphere/Structure/Canny.h>
#include <Radiometry/src/Detection/Sphere/Structure/Ransac.h>


namespace rad::detection::sphere{

struct Structure{
  //---------------------------

  //Step
  int state_step = rad::detection::VALIDATION;
  int state_data = rad::detection::NO_DATA;

  //Structures
  utl::media::Image image;
  rad::detection::structure::Hough hough;
  rad::detection::structure::Canny canny;
  rad::detection::structure::Bbox bbox;
  rad::detection::structure::Ransac ransac;

  //---------------------------
};

}
