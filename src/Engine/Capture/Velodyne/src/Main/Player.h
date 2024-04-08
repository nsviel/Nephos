#pragma once

#include <Utility/Specific/Common.h>

namespace vld::structure{class Main;}


namespace vld::main{

class Player
{
public:
  //Constructor / Destructor
  Player(vld::structure::Main* vld_struct);
  ~Player();

public:
  //Main function
  void start_playback();
  void stop_playback();
  void determine_range();
  void compute_visibility();
  void forward_index(int index);

  //Player function
  void player_pause(bool value);
  void player_play();
  void player_stop();
  void player_restart();
  void player_close();

private:
  vld::structure::Main* vld_struct;
};

}
