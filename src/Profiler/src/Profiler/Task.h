#pragma once

#include <Utility/Specific/common.h>


namespace prf::type{

struct Task{
  //---------------------------

  double time_beg;
  double time_end;
  std::string name;
  vec4 color = vec4(0, 0, 0, 0);

  //---------------------------
};

}
