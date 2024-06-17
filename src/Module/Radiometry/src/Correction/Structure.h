#pragma once

#include <Radiometry/src/Correction/Detection/Process.h>
#include <Radiometry/src/Correction/Structure/Circle.h>
#include <Radiometry/src/Correction/Structure/Hough.h>
#include <Radiometry/src/Correction/Structure/Canny.h>
#include <Radiometry/src/Correction/Structure/Ransac.h>
#include <Radiometry/src/Correction/Structure/Measure.h>
#include <Radiometry/src/Correction/Structure/Model.h>
#include <Radiometry/src/Correction/Structure/Plot.h>
#include <string>
#include <vector>


namespace rad::correction{

struct Structure{
  //---------------------------

  //General
  utl::media::Image image;
  int state_step = rad::correction::VALIDATION;
  int state_data = rad::correction::NO_DATA;

  //Detection stuff
  rad::correction::structure::Hough hough;
  rad::correction::structure::Canny canny;
  rad::correction::structure::Bbox bbox;
  rad::correction::structure::Ransac ransac;

  //Model stuff
  rad::correction::structure::Measure measure;
  rad::correction::structure::Plot plot;
  rad::correction::structure::Model model;

  //---------------------------
};

}
