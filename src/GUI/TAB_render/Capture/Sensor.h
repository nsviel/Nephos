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
  void show_info(k4n::dev::Sensor* sensor);

private:
  k4n::Node* node_kinect;
  k4n::dev::Swarm* k4n_swarm;
  k4n::utils::Transformation* k4n_transfo;
  
  int item_width;
};

}
