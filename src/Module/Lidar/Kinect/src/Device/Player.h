#pragma once

#include <Dynamic/src/Player/Player.h>
#include <Utility/Specific/Common.h>

namespace dyn::base{class Player;}
namespace k4n{class Node;}
namespace k4n::dev{class Master;}
namespace k4n::gui{class Player;}


namespace k4n::dev{

class Player : public dyn::base::Player
{
public:
  //Constructor / Destructor
  Player(k4n::Node* node_k4n, k4n::dev::Master* master);
  ~Player();

public:
  //Main function
  void player_update();
  void player_query(float value);
  void player_close();
  void player_stop();

  void element_info();
  void element_parameter();

public:
  k4n::gui::Player* gui_player;

  k4n::dev::Master* master;
};

}
