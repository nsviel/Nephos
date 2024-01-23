#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/src/Device/Namespace.h>
#include <Utility/Specific/common.h>
//#include <Engine/Capture/K4N/gui/Namespace.h>

class Engine;

namespace eng::k4n{


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

  inline eng::k4n::dev::Swarm* get_k4n_swarm(){return k4n_swarm;}

private:
  eng::k4n::dev::Swarm* k4n_swarm;
  eng::k4n::dev::Connection* k4n_connection;
  //gui::kinect::Stream* rnd_stream;
  //gui::kinect::Device* rnd_kinect;

  bool show_kinect;
};

}
