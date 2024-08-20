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


namespace rad::cor{

struct Structure{
  //---------------------------

  //General
  utl::media::Image image;
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
