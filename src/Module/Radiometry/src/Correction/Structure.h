#pragma once

#include <Radiometry/src/Correction/Detection/Process.h>
#include <Radiometry/src/Correction/Structure/Circle.h>
#include <Radiometry/src/Correction/Structure/Hough.h>
#include <Radiometry/src/Correction/Structure/Canny.h>
#include <Radiometry/src/Correction/Structure/Ransac.h>
#include <Radiometry/src/Correction/Structure/Measure.h>
#include <Radiometry/src/Correction/Structure/Model.h>
#include <Radiometry/src/Correction/Structure/Plot.h>
#include <Radiometry/src/Correction/Structure/State.h>


namespace rad::correction{

struct Structure{
  //---------------------------

  //General
  utl::media::Image image;
  rad::correction::structure::State state;

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
