#pragma once

#include <Radiometry/Correction/src/Detection/Process.h>
#include <Radiometry/Correction/src/Structure/Circle.h>
#include <Radiometry/Correction/src/Structure/Hough.h>
#include <Radiometry/Correction/src/Structure/Canny.h>
#include <Radiometry/Correction/src/Structure/Ransac.h>
#include <Radiometry/Correction/src/Structure/Measure.h>
#include <Radiometry/Correction/src/Structure/Model.h>
#include <Radiometry/Correction/src/Structure/Plot.h>
#include <Radiometry/Correction/src/Structure/State.h>


namespace rad::cor{

struct Structure{
  //---------------------------

  //General
  utl::base::Image image;
  rad::cor::structure::State state;

  //Detection stuff
  rad::cor::structure::Hough hough;
  rad::cor::structure::Canny canny;
  rad::cor::structure::Bbox bbox;
  rad::cor::structure::Ransac ransac;

  //Model stuff
  rad::cor::structure::Measure measure;
  rad::cor::structure::Plot plot;
  rad::cor::structure::Model model;

  //---------------------------
};

}
