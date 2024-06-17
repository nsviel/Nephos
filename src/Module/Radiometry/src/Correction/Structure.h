#pragma once

#include <Radiometry/src/Correction/Detection/Process.h>
#include <Radiometry/src/Correction/Structure/Circle.h>
#include <Radiometry/src/Correction/Structure/Hough.h>
#include <Radiometry/src/Correction/Structure/Canny.h>
#include <Radiometry/src/Correction/Structure/Ransac.h>
#include <Radiometry/src/Correction/Structure/Sphere.h>
#include <Radiometry/src/Correction/Structure/Optimization.h>
#include <Radiometry/src/Correction/Structure/Plot.h>
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
