#pragma once

#include <Operation/src/Attribut/Structure/Color.h>
#include <Operation/src/Attribut/Structure/Intensity.h>
#include <Operation/src/Attribut/Structure/Normal.h>


namespace ope{

struct Attribut{
  //---------------------------

  ope::attribut::Normal normal;
  ope::attribut::Intensity intensity;
  ope::attribut::Color color;

  //---------------------------
};

}
