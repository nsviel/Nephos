#pragma once

namespace dat::gph{class Selection;}
namespace ctr{class Node;}
namespace dat::ply{class Player;}


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
  dat::gph::Selection* dat_selection;
  dat::ply::Player* dyn_player;
};

}