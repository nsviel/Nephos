#pragma once

#include <Radiometry/src/Structure/Model/Measure.h>
#include <Radiometry/src/Structure/Model/Optimization.h>
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
