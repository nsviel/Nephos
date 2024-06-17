#pragma once

#include <Radiometry/Namespace.h>


namespace rad::calibration{

struct Structure{
  //---------------------------

  int state_step = rad::detection::VALIDATION;
  int state_data = rad::detection::NO_DATA;

  int nb_detection = 0;

  //---------------------------
};

}
