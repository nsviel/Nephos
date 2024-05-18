#pragma once

#include <Radiometry/src/Model/Structure/Measure.h>
#include <Radiometry/src/Model/Structure/Optimization.h>
#include <string>
#include <vector>


namespace rad::structure{

struct Model{
  //---------------------------

  rad::structure::Measure measure;
  rad::structure::Optimization optim;

  //---------------------------
};

}
