#pragma once

namespace ctr{class Node;}
namespace ctr{class Structure;}
namespace ctr{class Player;}


namespace ctr::gui{

class Player
{
public:
  //Constructor / Destructor
  Player(ctr::Node* node_control);
  ~Player();

public:
  //Main function
  void run_control();

  //Keyboard
  void control_keyboard();

private:
  ctr::Structure* ctr_struct;
  ctr::Player* ctr_player;
};

}
