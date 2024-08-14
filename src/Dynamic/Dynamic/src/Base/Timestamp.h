#pragma once

#include <Element/src/Base/Object.h>
#include <Profiler/src/Dynamic/Profiler.h>


namespace dyn::base{

struct Timestamp{
  //---------------------------

  float duration = -1;
  float begin = -1;
  float end = -1;
  float current = -1;
  float record = -1;

  //---------------------------
};

}
