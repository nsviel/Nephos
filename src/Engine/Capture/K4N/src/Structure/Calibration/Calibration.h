#pragma once

#include <K4N/src/Structure/Calibration/Hough.h>
#include <K4N/src/Structure/Calibration/Canny.h>
#include <K4N/src/Structure/Calibration/Bbox.h>


namespace k4n::structure{

struct Calibration{
  //---------------------------

  bool activated = false;
  
  k4n::structure::Hough hough;
  k4n::structure::Canny canny;
  k4n::structure::Bbox bbox;

  //---------------------------
};

}
