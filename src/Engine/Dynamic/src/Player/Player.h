#pragma once

#include <Dynamic/src/Base/State.h>
#include <Dynamic/src/Base/Timestamp.h>
#include <Utility/Specific/Common.h>

namespace dyn{class Node;}
namespace dat{class Selection;}


namespace dyn::player{

class Player
{
public:
  //Constructor / Destructor
  Player(dyn::Node* node_dynamic);
  ~Player();

  //Main function
  void update();
  void reset();

  void player_play();
  void player_pause();
  void player_stop();
  void player_restart();
  void player_record();
  void player_lock(bool value);
  void player_close();

  //Main function
  void manage_update(dat::base::Set* set);
  void manage_query(float value);
  void manage_restart();
  void manage_reset(dat::base::Set* set);
  void manage_configuration();
  void manage_forward();

  inline dyn::base::State* get_state(){return &state;}
  inline dyn::base::Timestamp* get_timestamp(){return &timestamp;}

public:
  dat::Selection* dat_selection;

  dyn::base::Timestamp timestamp;
  dyn::base::State state;
};

}
