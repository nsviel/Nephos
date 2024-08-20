#pragma once

#include <Base/Entity/Object.h>
#include <Profiler/src/Dynamic/Profiler.h>


namespace dyn::prc::base{

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
