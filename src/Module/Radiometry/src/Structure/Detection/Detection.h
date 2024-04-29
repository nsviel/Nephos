#pragma once

#include <Radiometry/src/Structure/Detection/Hough.h>
#include <Radiometry/src/Structure/Detection/Canny.h>
#include <Radiometry/src/Structure/Detection/Bbox.h>
#include <Radiometry/src/Structure/Detection/Ransac.h>
#include <Radiometry/src/Structure/Model/Measure.h>
#include <Radiometry/src/Structure/Model/Model.h>


namespace radio::structure{

struct Detection{
  //---------------------------

  radio::structure::Hough hough;
  radio::structure::Canny canny;
  radio::structure::Bbox bbox;
  radio::structure::Ransac ransac;

  //---------------------------
};

}
