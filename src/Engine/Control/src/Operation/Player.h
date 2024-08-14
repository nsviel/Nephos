#pragma once

namespace dat::graph{class Selection;}
namespace ctl{class Node;}
namespace dyn::player{class Player;}


namespace ctl::control{

class Player
{
public:
  //Constructor / Destructor
  Player(itf::Node* node_interface);
  ~Player();

public:
  //Main function
  void make_pause();
  void make_forward();
  void make_backward();

private:
  dat::graph::Selection* dat_selection;
  dyn::player::Player* dyn_player;
};

}
