#pragma once

#include <k4a/k4a.hpp>
#include <string>


namespace k4n::structure{

struct Configuration{
  //---------------------------

  k4n::structure::Depth_config depth;
  k4n::structure::Color_config color;
  k4n::structure::Infrared_config ir;

  //---------------------------
};

}
