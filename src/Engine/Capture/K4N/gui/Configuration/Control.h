#pragma once

#include <Utility/Specific/common.h>

namespace eng::k4n{class Node;}
namespace eng::k4n::dev{class Swarm;}


namespace eng::k4n::gui{

class Control
{
public:
  //Constructor / Destructor
  Control(eng::k4n::Node* node_k4n);
  ~Control();

public:
  //Main function
  void run_control();

  //Keyboard
  void control_keyboard();

private:
  eng::k4n::dev::Swarm* k4n_swarm;
};

}
