#pragma once

#include <Data/src/Base/Object.h>
#include <Profiler/src/Profiler/Graph/Profiler.h>


namespace dyn::player{

struct State{
  //---------------------------

  bool play = true;
  bool pause = false;
  bool restart = true;
  bool record = false;

  //---------------------------
};

}
