#pragma once


namespace k4n::structure{

struct Calibration{
  //---------------------------

  k4n::structure::Hough hough;
  k4n::structure::Canny canny;
  k4n::structure::Bbox bbox;

  //---------------------------
};

}
