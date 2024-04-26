#pragma once


namespace gui::player{

struct Structure{
  //---------------------------

  virtual void player_update(){}
  virtual void player_play(){}
  virtual void player_pause(bool value){}
  virtual void player_query_ts(float value){}
  virtual void player_stop(){}
  virtual void player_restart(){}
  virtual void player_record(){}
  virtual void player_close(){}

  utl::type::Set* set = nullptr;

  bool play = true;
  bool pause = false;
  bool restart = true;
  bool record = false;

  float duration = -1;
  float ts_beg = -1;
  float ts_end = -1;
  float ts_cur = -1;
  float ts_forward = 0;
  float ts_seek = -1;

  //---------------------------
};

}
