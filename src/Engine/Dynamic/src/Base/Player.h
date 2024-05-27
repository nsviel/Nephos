#pragma once

#include <Utility/Specific/Common.h>

namespace dat::base{class Set;}


namespace dyn::base{

class Player
{
public:
  //Constructor / Destructor
  Player(dat::base::Set* set);
  ~Player();

  //Main function
  virtual void player_play();
  virtual void player_pause();
  virtual void player_stop();
  virtual void player_restart();
  virtual void player_record();
  virtual void player_lock(bool value);
  virtual void player_update();
  virtual void player_close();
  virtual void player_query(float value);

public:
  dat::base::Set* set;

  std::string time = "%";
  utl::media::Path path;
  float size = 0;
  int fps_cur = 0;
  int fps_qry = 0;

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
};

}