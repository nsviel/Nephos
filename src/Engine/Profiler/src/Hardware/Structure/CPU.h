#pragma once

#include <string>


namespace prf::hardware::structure{

struct CPU{
  //---------------------------

  std::string name = "";
  float temperature = -1;
  int temperature_max = -1;
  int nb_core = -1;

  //---------------------------
};

}
