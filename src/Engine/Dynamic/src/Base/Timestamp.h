#pragma once

#include <Data/src/Base/Object.h>
#include <Profiler/src/Profiler/Graph/Profiler.h>


namespace dyn::base{

struct Timestamp{
  //---------------------------

  float duration = -1;
  float begin = -1;
  float end = -1;
  float current = -1;
  float forward = 0;
  float seek = -1;

  //---------------------------
};

}
