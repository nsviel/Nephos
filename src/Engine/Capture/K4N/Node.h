#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/Structure/Namespace.h>
#include <Utility/Specific/common.h>

class Engine;

namespace k4n{
class Swarm;


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
  void reset();

  inline k4n::Swarm* get_k4a_swarm(){return k4a_swarm;}

private:
  k4n::Swarm* k4a_swarm;
};

}
