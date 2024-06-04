#pragma once

#include <Utility/Specific/Common.h>


namespace prf::graph{

struct Task{
  //---------------------------

  double time_beg;
  double time_end;
  std::string name;
  vec4 color = vec4(0, 0, 0, 0);

  //---------------------------
};

}
