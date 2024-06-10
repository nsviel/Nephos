#pragma once

#include <Radiometry/src/Model/Structure/Sphere.h>
#include <Radiometry/src/Model/Structure/Optimization.h>
#include <Radiometry/src/Model/Structure/Plot.h>
#include <Radiometry/src/Model/Structure/Chart.h>


namespace rad::model{

struct Structure{
  //---------------------------

  rad::model::structure::Sphere sphere;
  rad::model::structure::Chart chart;
  rad::model::structure::Optimization optim;
  rad::model::structure::Plot plot;

  //---------------------------
};

}
