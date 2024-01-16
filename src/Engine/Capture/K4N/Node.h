#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Utility/Specific/common.h>

class Engine;

namespace k4n{


class Node
{
public:
  //Constructor / Destructor
  Node(Engine* engine);
  ~Node();

public:
  //Main function
  void init();
  void loop();

  inline k4n::dev::Swarm* get_k4a_swarm(){return k4a_swarm;}

private:
  k4n::dev::Swarm* k4a_swarm;
};

}
