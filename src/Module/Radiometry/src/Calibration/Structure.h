#pragma once

#include <Radiometry/src/Calibration/Structure/Optimization.h>
#include <Radiometry/src/Calibration/Structure/Plot.h>
#include <Radiometry/src/Calibration/Structure/Chart.h>


namespace rad::calibration::model{

struct Structure{
  //---------------------------

  rad::calibration::structure::Chart chart;
  rad::calibration::structure::Optimization optim;
  rad::calibration::structure::Plot plot;

  //---------------------------
};

}
