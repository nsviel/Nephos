#pragma once

#include <Radiometry/src/Correction/Detection/Structure/Circle.h>
#include <Radiometry/src/Correction/Detection/Structure/Hough.h>
#include <Radiometry/src/Correction/Detection/Structure/Canny.h>
#include <Radiometry/src/Correction/Detection/Structure/Ransac.h>
#include <Radiometry/src/Model/Sphere/Structure/Sphere.h>
#include <Radiometry/src/Model/Sphere/Structure/Optimization.h>
#include <Radiometry/src/Model/Sphere/Structure/Plot.h>
#include <string>
#include <vector>


namespace rad::correction{

struct Structure{
  //---------------------------

  utl::media::Image image;

  //Step
  int state_step = rad::correction::VALIDATION;
  int state_data = rad::correction::NO_DATA;

  //Structures
  rad::correction::structure::Hough hough;
  rad::correction::structure::Canny canny;
  rad::correction::structure::Bbox bbox;
  rad::correction::structure::Ransac ransac;

  rad::correction::structure::Sphere sphere;
  rad::correction::structure::Optimization optim;
  rad::correction::structure::Plot plot;

  //---------------------------
};

}
