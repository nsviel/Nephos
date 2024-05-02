#pragma once

#include <Dynamic/src/Base/Player.h>
#include <Utility/Specific/Common.h>


namespace k4n::dev{

class Player : public dyn::Player
{
public:
  //Constructor / Destructor
  Player(dat::base::Set* set);
  ~Player();

  //Main function
  void player_update();
  void player_play();
  void player_pause();
  void player_query_ts(float value);
  void player_stop();
  void player_restart();
  void player_record();
  void player_close();
  void player_lock();

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
