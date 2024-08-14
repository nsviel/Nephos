namespace ctl#pragma once

namespace ctl{class Node;}
namespace ctl{class Structure;}
namespace ctl::control{class Player;}


namespace ctl::gui{

class Player
{
public:
  //Constructor / Destructor
  Player(itf::Node* node_interface);
  ~Player();

public:
  //Main function
  void run_control();

  //Keyboard
  void control_keyboard();

private:
  itf::Structure* itf_struct;
  itf::control::Player* itf_player;
};

}
