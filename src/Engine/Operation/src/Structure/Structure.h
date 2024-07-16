#pragma once

#include <Operation/src/Structure/Attribut.h>
#include <Operation/src/Structure/Colorization.h>


namespace ope{

struct Structure{
  //---------------------------

  ope::attribut::Normal normal;
  ope::attribut::Intensity intensity;
  ope::attribut::Color color;

  //---------------------------
};

}
