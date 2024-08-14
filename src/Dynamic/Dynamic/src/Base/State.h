#pragma once

#include <Data/src/Base/Object.h>
#include <Profiler/src/Dynamic/Profiler.h>


namespace dyn::base{

struct State{
  //---------------------------

  bool play = true;
  bool pause = false;
  bool replay = true;
  bool record = false;
  bool locked = false;
  bool query = false;

  //---------------------------
};

}
