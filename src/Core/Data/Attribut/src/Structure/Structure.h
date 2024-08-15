#pragma once

#include <Operation/src/Attribut/Structure/Color.h>
#include <Operation/src/Attribut/Structure/Intensity.h>
#include <Operation/src/Attribut/Structure/Normal.h>


namespace ope::attribut{

struct Structure{
  //---------------------------

  ope::attribut::structure::Normal normal;
  ope::attribut::structure::Intensity intensity;
  ope::attribut::structure::Color color;

  //---------------------------
};

}
