#pragma once

#include <Camera/src/Object/Entity.h>
#include <vector>


namespace cam::structure{

struct Path{
  //---------------------------

  bool enable = false;
  float amplitude = 5.0f; // Maximum value
  float frequency = 0.1f; // Number of cycles per second
  float phase = 0.0f; // Phase shift
  float lambda = 1.0f; // Phase shift

  //---------------------------
};

}
