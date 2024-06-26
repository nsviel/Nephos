#pragma once

#include <Data/src/Base/Object.h>
#include <Profiler/src/Graph/Profiler.h>


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
