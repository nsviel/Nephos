#pragma once

#include <Radiometry/Namespace.h>


namespace rad::detection::chart{

struct Structure{
  //---------------------------

  int state_step = rad::detection::VALIDATION;
  int state_data = rad::detection::NO_DATA;

  //---------------------------
};

}
