#pragma once

#include <Utility/Specific/Common.h>


namespace dyn{

class Player
{
public:
  //Main function
  virtual void player_update(){}
  virtual void player_play(){}
  virtual void player_pause(){}
  virtual void player_query_ts(float value){}
  virtual void player_stop(){}
  virtual void player_restart(){}
  virtual void player_record(){}
  virtual void player_close(){}
  virtual void player_lock(){}

  inline bool& get_state_play(){return play;}
  inline bool& get_state_pause(){return pause;}
  inline bool& get_state_restart(){return restart;}
  inline bool& get_state_record(){return record;}
  inline bool& get_state_locked(){return locked;}
  inline float get_duration(){return duration;}
  inline float& get_ts_beg(){return ts_beg;}
  inline float& get_ts_end(){return ts_end;}
  inline float& get_ts_cur(){return ts_cur;}
  inline float& get_ts_forward(){return ts_forward;}
  inline void set_duration(float value){this->duration = value;}

private:
  bool play = true;
  bool pause = false;
  bool restart = true;
  bool record = false;
  bool locked = false;

  float duration = -1;
  float ts_beg = -1;
  float ts_end = -1;
  float ts_cur = -1;
  float ts_forward = 0;
  float ts_seek = -1;
};

}
