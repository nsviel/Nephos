#pragma once

namespace dat::graph{class Selection;}
namespace dyn{class Node;}
namespace dyn::player{class Player;}


namespace dyn::gui{

class Control
{
public:
  //Constructor / Destructor
  Control(dyn::Node* node_dynamic);
  ~Control();

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
