#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/src/Device/Namespace.h>
#include <Utility/Specific/common.h>
//#include <Engine/Capture/K4N/gui/Namespace.h>

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

  inline k4n::src::dev::Swarm* get_k4n_swarm(){return k4n_swarm;}

private:
  k4n::src::dev::Swarm* k4n_swarm;
  k4n::src::dev::Connection* k4n_connection;
  //gui::kinect::Stream* rnd_stream;
  //gui::kinect::Device* rnd_kinect;

  bool show_kinect;
};

}
