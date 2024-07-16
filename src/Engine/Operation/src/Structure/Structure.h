#pragma once

#include <Operation/src/Structure/Attribut/Color.h>
#include <Operation/src/Structure/Attribut/Intensity.h>
#include <Operation/src/Structure/Attribut/Normal.h>


namespace ope{

struct Structure{
  //---------------------------

  ope::attribut::Normal normal;
  ope::attribut::Intensity intensity;
  ope::attribut::Color color;

  //---------------------------
};

}
