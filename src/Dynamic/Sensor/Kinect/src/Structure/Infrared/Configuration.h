#pragma once

#include <k4a/k4a.hpp>


namespace k4n::str::infra{

struct Configuration{
  //---------------------------

  uint16_t level_min = 0;
  uint16_t level_max = 1000;
  bool enabled = true;
  int division = 1000;

  //---------------------------
};

}
