#pragma once

#include <Radiometry/src/Structure/Detection/Hough.h>
#include <Radiometry/src/Structure/Detection/Canny.h>
#include <Radiometry/src/Structure/Detection/Bbox.h>
#include <Radiometry/src/Structure/Detection/Ransac.h>
#include <Radiometry/src/Structure/Model/Measure.h>
#include <Radiometry/src/Structure/Model/Model.h>


namespace rad::structure{

struct Detection{
  //---------------------------

  rad::structure::Hough hough;
  rad::structure::Canny canny;
  rad::structure::Bbox bbox;
  rad::structure::Ransac ransac;

  //---------------------------
};

}
