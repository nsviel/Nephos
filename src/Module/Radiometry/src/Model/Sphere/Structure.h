#pragma once

#include <Radiometry/src/Model/Sphere/Structure/Sphere.h>
#include <Radiometry/src/Model/Sphere/Structure/Optimization.h>
#include <Radiometry/src/Model/Sphere/Structure/Plot.h>


namespace rad::model::sphere{

struct Structure{
  //---------------------------

  rad::model::sphere::structure::Sphere sphere;
  rad::model::sphere::structure::Optimization optim;
  rad::model::sphere::structure::Plot plot;

  //---------------------------
};

}
