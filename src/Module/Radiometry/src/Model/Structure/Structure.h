#pragma once

#include <Radiometry/src/Model/Structure/Measure.h>
#include <Radiometry/src/Model/Structure/Optimization.h>
#include <Radiometry/src/Model/Structure/Plot.h>
#include <string>
#include <vector>


namespace rad::model{

struct Structure{
  //---------------------------

  rad::model::structure::Measure measure;
  rad::model::structure::Optimization optim;
  rad::model::structure::Plot plot;

  //---------------------------
};

}
