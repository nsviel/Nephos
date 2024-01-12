#pragma once

#include <Engine/Capture/K4N/Structure/Namespace.h>
#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/Device/Namespace.h>
#include <Utility/Specific/common.h>

#include <k4a/k4a.h>
#include <k4a/k4a.hpp>

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
  void reset();

  inline k4n::truc::Swarm* get_k4a_swarm(){return k4a_swarm;}

private:
  k4n::truc::Swarm* k4a_swarm;
};

}
