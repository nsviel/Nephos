#pragma once

#include <Engine/Capture/Kinect/Structure/Namespace.h>
#include <Engine/Capture/Kinect/Thread/Namespace.h>
#include <Engine/Capture/Kinect/Namespace.h>
#include <Engine/Capture/Kinect/Device/K4A_swarm.h>
#include <Engine/Capture/Kinect/Device/K4A_device.h>
#include <Utility/Specific/common.h>

#include <k4a/k4a.h>
#include <k4a/k4a.hpp>

class Engine;


namespace eng::kinect{

class Kinect
{
public:
  //Constructor / Destructor
  Kinect(Engine* engine);
  ~Kinect();

public:
  //Main function
  void init();
  void restart_capture();
  void loop();

  inline K4A_swarm* get_k4a_swarm(){return k4a_swarm;}

private:
  K4A_swarm* k4a_swarm;
  eng::kinect::thread::K4A_connection* k4a_connection;
};

}
