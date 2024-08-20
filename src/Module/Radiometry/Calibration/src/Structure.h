#pragma once

#include <Radiometry/src/Calibration/Detection/Process.h>
#include <Radiometry/src/Calibration/Structure/Optimization.h>
#include <Radiometry/src/Calibration/Structure/Plot.h>
#include <Radiometry/src/Calibration/Structure/Chart.h>
#include <Radiometry/src/Calibration/Structure/State.h>
#include <Radiometry/src/Calibration/Structure/Canny.h>
#include <Radiometry/src/Calibration/Structure/Hough.h>


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
