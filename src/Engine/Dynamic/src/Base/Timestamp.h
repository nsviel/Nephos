#pragma once

#include <Data/src/Base/Object.h>
#include <Profiler/src/Profiler/Graph/Profiler.h>


namespace dyn::base{

struct Timestamp{
  //---------------------------

  bool play = true;
  bool pause = false;
  bool restart = true;
  bool record = false;

  float ts_duration = -1;
  float ts_beg = -1;
  float ts_end = -1;
  float ts_cur = -1;
  float ts_forward = 0;
  float ts_seek = -1;

  //---------------------------
};

}
