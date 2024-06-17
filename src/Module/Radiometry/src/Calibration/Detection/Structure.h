#pragma once

#include <Radiometry/Namespace.h>


namespace rad::calibration{

struct Structure{
  //---------------------------

  int state_step = rad::correction::VALIDATION;
  int state_data = rad::correction::NO_DATA;

  int nb_detection = 0;

  //---------------------------
};

}
