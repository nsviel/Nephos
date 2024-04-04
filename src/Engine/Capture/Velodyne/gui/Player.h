#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace vld{class Node;}
namespace vld::processing{class Player;}
namespace vld::structure{class Main;}


namespace vld::gui{

class Player
{
public:
  //Constructor / Destructor
  Player(vld::structure::Main* vld_struct);
  ~Player();

public:
  //Main function
  void draw_player();

  //Subfunction
  void player_slider();
  void player_start();
  void player_stop();
  void player_repeat();
  void player_close();
  void player_lock();

private:
  vld::structure::Main* vld_struct;
  vld::processing::Player* vld_player;
};

}
