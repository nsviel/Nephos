#pragma once

#include <Radiometry/src/Calibration/Detection/Process.h>
#include <Radiometry/src/Calibration/Structure/Optimization.h>
#include <Radiometry/src/Calibration/Structure/Plot.h>
#include <Radiometry/src/Calibration/Structure/Chart.h>


namespace rad::calibration{

struct Structure{
  //---------------------------

  int state_step = rad::calibration::VALIDATION;
  int state_data = rad::calibration::NO_DATA;

  int nb_detection = 0;


  rad::calibration::structure::Chart chart;
  rad::calibration::structure::Optimization optim;
  rad::calibration::structure::Plot plot;

  //---------------------------
};

}
