#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>

class GUI;


namespace gui::kinect{

class Sensor
{
public:
  //Constructor / Destructor
  Sensor(k4n::Node* node_kinect);
  ~Sensor();

  //Main function

private:
  k4n::Node* node_kinect;
  k4n::dev::Swarm* k4n_swarm;

  int item_width;
};

}
