#pragma once

#include <Operation/src/Attribut/Structure/Color.h>
#include <Operation/src/Attribut/Structure/Intensity.h>
#include <Operation/src/Attribut/Structure/Normal.h>
#include <Operation/src/Attribut/Structure/Heatmap.h>


namespace ope{

struct Attribut{
  //---------------------------

  ope::attribut::Normal normal;
  ope::attribut::Intensity intensity;
  ope::attribut::Color color;
  ope::attribut::Heatmap heatmap;

  //---------------------------
};

}
