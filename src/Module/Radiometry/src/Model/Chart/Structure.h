#pragma once

#include <Radiometry/src/Model/Chart/Structure/Optimization.h>
#include <Radiometry/src/Model/Chart/Structure/Plot.h>
#include <Radiometry/src/Model/Chart/Structure/Chart.h>


namespace rad::model::chart{

struct Structure{
  //---------------------------

  rad::model::chart::structure::Chart chart;
  rad::model::chart::structure::Optimization optim;
  rad::model::chart::structure::Plot plot;

  //---------------------------
};

}
