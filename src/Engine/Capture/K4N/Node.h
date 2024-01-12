#pragma once

#include <Engine/Capture/K4N/Structure/Namespace.h>
#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/Device/K4A_swarm.h>
#include <Engine/Capture/K4N/Device/K4A_device.h>
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

  inline K4A_swarm* get_k4a_swarm(){return k4a_swarm;}

private:
  K4A_swarm* k4a_swarm;
};

}
