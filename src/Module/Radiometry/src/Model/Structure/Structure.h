#pragma once

#include <Radiometry/src/Model/Structure/Sphere.h>
#include <Radiometry/src/Model/Structure/Optimization.h>
#include <Radiometry/src/Model/Structure/Plot.h>
#include <string>
#include <vector>


namespace rad::model{

struct Structure{
  //---------------------------

  rad::model::structure::Sphere sphere;
  rad::model::structure::Optimization optim;
  rad::model::structure::Plot plot;

  //---------------------------
};

}
