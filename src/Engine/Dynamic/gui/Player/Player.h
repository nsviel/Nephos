#pragma once

#include <Utility/Specific/Common.h>

namespace dat{class Selection;}
namespace dyn{class Node;}
namespace dyn::player{class Player;}


namespace dyn::gui{

class Player
{
public:
  //Constructor / Destructor
  Player(dyn::Node* node_dynamic);
  ~Player();

  //Main function
  void design_player();

  //Player function
  void player_slider();
  void player_start();
  void player_stop();
  void player_repeat();
  void player_record();
  void player_close();
  void player_lock();

private:
  dyn::player::Player* dyn_player;
  dat::Selection* dat_selection;
};

}
