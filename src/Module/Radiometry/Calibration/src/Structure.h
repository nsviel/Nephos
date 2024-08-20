#pragma once

#include <Radiometry/Calibration/src/Detection/Process.h>
#include <Radiometry/Calibration/src/Structure/Optimization.h>
#include <Radiometry/Calibration/src/Structure/Plot.h>
#include <Radiometry/Calibration/src/Structure/Chart.h>
#include <Radiometry/Calibration/src/Structure/State.h>
#include <Radiometry/Calibration/src/Structure/Canny.h>
#include <Radiometry/Calibration/src/Structure/Hough.h>


namespace rad::cal{

struct Structure{
  //---------------------------

  int nb_detection = 0;

  rad::cal::structure::State state;

  rad::cal::structure::Canny canny;
  rad::cal::structure::Hough hough;
  rad::cal::structure::Chart chart;
  rad::cal::structure::Optimization optim;
  rad::cal::structure::Plot plot;

  //---------------------------
};

}
