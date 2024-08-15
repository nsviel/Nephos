#pragma once

#include <Radiometry/src/Calibration/Detection/Process.h>
#include <Radiometry/src/Calibration/Structure/Optimization.h>
#include <Radiometry/src/Calibration/Structure/Plot.h>
#include <Radiometry/src/Calibration/Structure/Chart.h>
#include <Radiometry/src/Calibration/Structure/State.h>
#include <Radiometry/src/Calibration/Structure/Canny.h>
#include <Radiometry/src/Calibration/Structure/Hough.h>


namespace rad::calibration{

struct Structure{
  //---------------------------

  int nb_detection = 0;

  rad::calibration::structure::State state;

  rad::calibration::structure::Canny canny;
  rad::calibration::structure::Hough hough;
  rad::calibration::structure::Chart chart;
  rad::calibration::structure::Optimization optim;
  rad::calibration::structure::Plot plot;

  //---------------------------
};

}
