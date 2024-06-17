#pragma once

#include <Radiometry/src/Model/Sphere/Structure/Sphere.h>
#include <Radiometry/src/Model/Sphere/Structure/Optimization.h>
#include <Radiometry/src/Model/Sphere/Structure/Plot.h>


namespace rad::correction{

struct Structure{
  //---------------------------

  rad::correction::structure::Sphere sphere;
  rad::correction::structure::Optimization optim;
  rad::correction::structure::Plot plot;

  //---------------------------
};

}
