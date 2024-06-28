#pragma once

namespace dat::graph{class Selection;}
namespace itf{class Node;}
namespace dyn::player{class Player;}


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
  dat::graph::Selection* dat_selection;
  dyn::player::Player* dyn_player;
};

}
