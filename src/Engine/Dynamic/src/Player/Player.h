#pragma once

#include <Dynamic/src/Player/State.h>
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
  void player_play();
  void player_pause();
  void player_stop();
  void player_restart();
  void player_record();
  void player_lock(bool value);
  void player_close();

  inline dyn::player::State* get_state(){return &state;}
  inline dyn::base::Timestamp* get_timestamp(){return &timestamp;}

public:
  dat::Selection* dat_selection;

  dyn::base::Timestamp timestamp;
  dyn::player::State state;
};

}
