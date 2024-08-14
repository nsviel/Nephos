#pragma once

namespace dat::graph{class Selection;}
namespace ctr{class Node;}
namespace dyn::player{class Player;}


namespace ctr{

class Player
{
public:
  //Constructor / Destructor
  Player(ctr::Node* node_control);
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
