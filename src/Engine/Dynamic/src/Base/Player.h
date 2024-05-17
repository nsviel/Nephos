#pragma once

#include <Utility/Specific/Common.h>


namespace dyn::base{

struct Player{
  virtual void player_update(){}
  virtual void player_play(){}
  virtual void player_pause(){}
  virtual void player_query_ts(float value){}
  virtual void player_stop(){}
  virtual void player_restart(){}
  virtual void player_record(){}
  virtual void player_close(){}
  virtual void player_lock(){}
  virtual void player_info(){}

  bool player_enable = false;
  bool play = true;
  bool pause = false;
  bool restart = true;
  bool record = false;
  bool locked = false;

  float ts_duration = -1;
  float ts_beg = -1;
  float ts_end = -1;
  float ts_cur = -1;
  float ts_forward = 0;
  float ts_seek = -1;
};

}
