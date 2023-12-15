#pragma once

#include <string>


namespace eng::kinect::structure{

struct Player{
  //---------------------------

  bool play = true;
  bool pause = false;
  bool restart = true;
  bool record = false;

  float duration = -1;
  float ts_beg = -1;
  float ts_end = -1;
  float ts_cur = -1;
  float ts_seek = -1;

  //---------------------------
};

}
