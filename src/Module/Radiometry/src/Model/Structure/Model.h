#pragma once

#include <Radiometry/src/Model/Structure/Measure.h>
#include <Radiometry/src/Model/Structure/Optimization.h>
#include <Radiometry/src/Model/Structure/Plot.h>
#include <string>
#include <vector>


namespace rad::structure{

struct Model{
  //---------------------------

  rad::structure::Measure measure;
  rad::structure::Optimization optim;
  rad::structure::Plot plot;

  //---------------------------
};

}
