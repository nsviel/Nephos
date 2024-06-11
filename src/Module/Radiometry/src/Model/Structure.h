#pragma once

#include <Radiometry/src/Model/Sphere/Structure.h>
#include <Radiometry/src/Model/Chart/Structure.h>


namespace rad::model{

struct Structure{
  //---------------------------

  rad::model::sphere::Structure sphere;
  rad::model::chart::Structure chart;

  //---------------------------
};

}
