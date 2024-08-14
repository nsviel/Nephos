#pragma once

namespace itf{class Node;}
namespace itf{class Structure;}
namespace itf::control{class Player;}


namespace itf::gui{

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
