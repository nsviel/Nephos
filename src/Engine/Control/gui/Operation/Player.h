#pragma once

namespace ctl{class Node;}
namespace ctl{class Structure;}
namespace ctl{class Player;}


namespace ctl::gui{

class Player
{
public:
  //Constructor / Destructor
  Player(ctl::Node* node_control);
  ~Player();

public:
  //Main function
  void run_control();

  //Keyboard
  void control_keyboard();

private:
  ctl::Structure* ctl_struct;
  ctl::Player* ctl_player;
};

}
