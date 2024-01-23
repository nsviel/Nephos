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
  void show_sensor(k4n::src::dev::Sensor* sensor);

  //Subfunction
  void show_sensor_info(k4n::src::dev::Sensor* sensor);
  void show_sensor_transfo(k4n::src::dev::Sensor* sensor);

private:
  k4n::Node* node_kinect;
  k4n::src::dev::Swarm* k4n_swarm;
  k4n::src::utils::Transformation* k4n_transfo;

  int item_width;
};

}
