#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Swarm;}


namespace k4n::gui{

class Control
{
public:
  //Constructor / Destructor
  Control(k4n::Node* node_k4n);
  ~Control();

public:
  //Main function
  void run_control();

  //Keyboard
  void control_keyboard();

private:
  k4n::dev::Swarm* k4n_swarm;
};

}
