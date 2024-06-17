#pragma once

#include <Radiometry/src/Model/Chart/Structure/Optimization.h>
#include <Radiometry/src/Model/Chart/Structure/Plot.h>
#include <Radiometry/src/Model/Chart/Structure/Chart.h>


namespace rad::calibration{

struct Structure{
  //---------------------------

  rad::calibration::structure::Chart chart;
  rad::calibration::structure::Optimization optim;
  rad::calibration::structure::Plot plot;

  //---------------------------
};

}
