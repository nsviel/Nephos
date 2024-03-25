#pragma once

#include <K4N/src/Structure/Matching/Hough.h>
#include <K4N/src/Structure/Matching/Canny.h>
#include <K4N/src/Structure/Matching/Bbox.h>
#include <K4N/src/Structure/Matching/Calibration.h>


namespace k4n::structure{

struct Matching{
  //---------------------------

  bool panel_open = false;

  k4n::structure::Hough hough;
  k4n::structure::Canny canny;
  k4n::structure::Bbox bbox;
  k4n::structure::Calibration calibration;

  //---------------------------
};

}
