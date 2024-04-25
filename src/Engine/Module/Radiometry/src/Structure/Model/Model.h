#pragma once

#include <Radiometry/src/Structure/Model/Measure.h>
#include <Radiometry/src/Structure/Model/Optimization.h>
#include <string>
#include <vector>


namespace radio::structure{

struct Model{
  //---------------------------

  radio::structure::Measure measure;
  radio::structure::Optimization optim;

  //---------------------------
};

}
